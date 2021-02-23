#ifndef TP_WOLFENSTEIN_SERVER_SRC_SERVER_ACCEPTOR_H_
#define TP_WOLFENSTEIN_SERVER_SRC_SERVER_ACCEPTOR_H_

#include <vector>
#include <atomic>
#include "server/events/game_handler.h"
#include "common/network_acceptor.h"
#include "common/network_error.h"
#include "common/network_connection.h"
#include "common/thread.h"
#include "matches.h"
#include "server_routes.h"

#define CREATE_GAME "0"
#define JOIN_GAME "1"
#define SUCCESS "2"
#define ERROR "3"
#define BACK "4"

class ServerMenuHandler : public Thread{
  NetworkConnection socket;
  Matches& matches;

 public:
  explicit ServerMenuHandler(NetworkConnection _socket, Matches& _matches) :
    socket(std::move(_socket)), matches(_matches) {};

  void run() override {
      try {
          while (true) {
              std::string player_choice;
              std::string answer;
              socket.recv_msg(player_choice); // Recibo el tipo de evento
              if (player_choice == CREATE_GAME) {
                  socket.recv_msg(answer);
                  if (answer == BACK) continue;
                  int id = createGame(socket, answer);
                  joinGame(id, std::move(socket));
                  break;
              } else if (player_choice == JOIN_GAME){
                  matches.killDead();
                  matches.sendGames(socket);
                  socket.recv_msg(answer);
                  if (answer == BACK) continue;
                  int game_id_to_connect = std::stoi(answer);
                  if (matches.canJoinPlayer(game_id_to_connect)) {
                      socket.send_msg(SUCCESS);
                      joinGame(game_id_to_connect, std::move(socket));
                      break;
                  } else { socket.send_msg(ERROR); }
              }
          }
      } catch (NetworkError& e) { return; }
  }

  int createGame(NetworkConnection& skt, std::string& options) {

    std::vector<int> game_options = split(options); // minimos/maximos/bots/duracion
    std::string map_path;
    skt.recv_msg(map_path);
    auto new_game = new GameHandler(map_path, CONFIG_PATH, game_options[0],
                                    game_options[1], game_options[2],
                                    matches.getSize(),game_options[3]*60);

    skt.send_msg(SUCCESS);
    std::cout << "[Server] New Game created with id: " << matches.getSize() << "\n";
    new_game->start();
    matches.addNewMatch(new_game);
    return matches.getSize() - 1;
  }

  bool joinGame(int game_id, NetworkConnection socket) {
    if (matches.canJoinPlayer(game_id)) { // Ya esta afuera esta logica
      try {
        matches.addNewPlayer(game_id, std::move(socket));
        std::cout << "[Server] New player connected to game " << game_id << "\n";
      } catch (const NetworkError& e) { return false; }
      return true;
    } return false;
  }

  std::vector<int> split(const std::string& bytes) {
    std::vector<int> buffer;
    std::stringstream ss(bytes);
    std::string s;
    while (std::getline(ss, s, '/')) {
      if (s.empty()) continue;
      buffer.push_back(std::stoi(s));
    }
    return buffer;
  }

  void stop() {
      socket.shutdownAll();
  }
};

#endif //TP_WOLFENSTEIN_SERVER_SRC_SERVER_ACCEPTOR_H_
