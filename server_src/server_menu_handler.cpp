#include "server/server_menu_handler.h"

ServerMenuHandler::ServerMenuHandler(NetworkConnection _socket, Matches& _matches) :
    socket(std::move(_socket)), matches(_matches) {}

void ServerMenuHandler::run() {
  std::cout << "[ServerMenuHandler] Started.\n";
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
      } else if (player_choice == JOIN_GAME) {
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
  std::cout << "[ServerMenuHandler] Stopping.\n";
}

int ServerMenuHandler::createGame(NetworkConnection& skt, std::string& options) {

  std::vector<int> game_options = split(options); // minimos/maximos/bots/duracion
  std::string map_path;
  skt.recv_msg(map_path);
  auto new_game = new GameHandler(map_path, CONFIG_PATH, game_options[0],
                                  game_options[1], game_options[2],
                                  matches.getSize(), game_options[3] * 60);

  skt.send_msg(SUCCESS);
  std::string newGameCreated = "[Server] New Game created with id: " + std::to_string(matches.getSize()) + "\n";
  std::cout << newGameCreated;
  new_game->start();
  matches.addNewMatch(new_game);
  return matches.getSize() - 1;
}

bool ServerMenuHandler::joinGame(int game_id, NetworkConnection socket) {
  if (matches.canJoinPlayer(game_id)) {
    try {
      matches.addNewPlayer(game_id, std::move(socket));
      std::string newPlayerConnectedToGame = "[Server] New player connected to game " + std::to_string(game_id) + "\n";
      std::cout << newPlayerConnectedToGame;
    } catch (const NetworkError& e) { return false; }
    return true;
  }
  return false;
}

std::vector<int> ServerMenuHandler::split(const std::string& bytes) {
  std::vector<int> buffer;
  std::stringstream ss(bytes);
  std::string s;
  while (std::getline(ss, s, '/')) {
    if (s.empty()) continue;
    buffer.push_back(std::stoi(s));
  }
  return buffer;
}

void ServerMenuHandler::stop() {
  socket.shutdownAll();
}