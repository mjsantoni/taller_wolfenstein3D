#include <algorithm>
#include "server/server.h"
#include "server_routes.h"

Server::Server(NetworkAcceptor socket) :
    networkAcceptor(std::move(socket)),
    accepting_connections(true) {
}

#define CREATE_GAME "0"
#define JOIN_GAME "1"
#define SUCCESS "2"
#define ERROR "3"
#define BACK "4"

void Server::run() {
  std::cout << "[Server] Started.\n";
  while (accepting_connections) {
    try {
      NetworkConnection socket = std::move(networkAcceptor.acceptConnection());
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
          killDead();
          sendGames(socket);
          socket.recv_msg(answer);
          if (answer == BACK) continue;
          int game_id_to_connect = std::stoi(answer);
          if (matches[game_id_to_connect]->canJoinPlayer()) {
            socket.send_msg(SUCCESS);
            joinGame(game_id_to_connect, std::move(socket));
          } else { socket.send_msg(ERROR); }
        }
      }
    } catch (const NetworkError& e) { continue; }
    killDead();
    usleep(100000);
  }
  stopGames();
  std::cout << "[Server] Finished all in-progress games\n";
}

static bool is_null(GameHandler* gh) { return !gh; }

/* CLEAN DEAD GAMES */
void Server::killDead() {
  int i = 0;
  for (auto& game : matches) {
    if (game->ended()) {
      game->join();
      delete game;
      matches[i] = nullptr;
    }
    i++;
  }
  matches.erase(std::remove_if(matches.begin(), matches.end(), is_null),
                matches.end());
}

void Server::stopGames() {
  for (auto& th_game : matches) {
    th_game->stop();
    th_game->join();
    delete th_game;
  }
}

int Server::createGame(NetworkConnection& skt, std::string& options) {

  std::vector<int> game_options = split(options); // minimos/maximos/bots/duracion
  std::string map_path;
  skt.recv_msg(map_path);
  auto new_game = new GameHandler(map_path, CONFIG_PATH, game_options[0],
                                  game_options[1], game_options[2],
                                  matches.size(),game_options[3]*60);

  skt.send_msg(SUCCESS);
  std::cout << "[Server] New Game created with id: " << matches.size() << "\n";
  new_game->start();
  matches.push_back(new_game);
  return matches.size() - 1;
}

bool Server::joinGame(int game_id, NetworkConnection socket) {
  if (matches[game_id]->canJoinPlayer()) { // Ya esta afuera esta logica
    try {
      matches[game_id]->addNewPlayer(std::move(socket));
      std::cout << "[Server] New player connected to game " << game_id << "\n";
    } catch (const NetworkError& e) { return false; }
    return true;
  } return false;
}

std::vector<int> Server::split(const std::string& bytes) {
  std::vector<int> buffer;
  std::stringstream ss(bytes);
  std::string s;
  while (std::getline(ss, s, '/')) {
    if (s.empty()) continue;
    buffer.push_back(std::stoi(s));
  }
  return buffer;
}

void Server::sendGames(NetworkConnection& socket) {
  for (auto& game : matches) {
    if (game->canJoinPlayer()) {
      socket.send_msg(game->getInformation());
    }
  }
  socket.send_msg(SUCCESS);
}

void Server::stop() {
  accepting_connections = false;
  networkAcceptor.closeSocket();
}

Server::~Server() {}
