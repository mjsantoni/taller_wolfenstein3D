#include <algorithm>
#include "server/server.h"
#include "routes_server.h"

Server::Server(NetworkAcceptor socket) :
        networkAcceptor(std::move(socket)),
        accepting_connections(true) {
    maps.emplace_back("map.yaml");
}

#define CREATE_GAME "0"
#define JOIN_GAME "1"
#define SUCCESS "2"
#define ERROR "3"
#define BACK "4"

void Server::run() {
    //std::string name = "map.yaml";
    //createGame(name, 1, 5, 0,10);

    std::cout << "[Server] Started.\n";
    while (accepting_connections) {
        try {
            NetworkConnection socket = std::move(networkAcceptor.acceptConnection());
            //std::cout << "Recibi tal opcion: " << player_choice << "\n";
            while (true) {
                std::string player_choice;
                socket.recv_msg(player_choice); // Recibo el tipo de evento
                if (player_choice == CREATE_GAME) {
                    std::string options;
                    socket.recv_msg(options);
                    std::cout << "Me paso estas opciones: " << options << "\n";
                    if (options == BACK) continue;

                    std::vector<int> game_options = split(options); // minimos/maximos/bots/duracion
                    std::string map_path;
                    socket.recv_msg(map_path);
                    int new_game_id = createGame(map_path, game_options[0],
                                                 game_options[1], game_options[2],
                                                 game_options[3]);
                    socket.send_msg(SUCCESS);
                    joinGame(new_game_id, std::move(socket));
                    break;

                } else {
                    killDead();
                    sendGames(socket);
                    std::string game_choice;
                    socket.recv_msg(game_choice);
                    if (game_choice == BACK) continue;
                    
                    int game_id_to_connect = std::stoi(game_choice);
                    std::cout << "El player se quiere unir al game: " << game_choice << "\n";
                    if (matches[game_id_to_connect]->canJoinPlayer()) {
                        socket.send_msg(SUCCESS);
                        joinGame(game_id_to_connect, std::move(socket));
                    } else {
                        socket.send_msg(ERROR);
                        continue;
                    }
                }
            }
        } catch (const NetworkError& e) { continue; }
        killDead();
        usleep(100000);
    }

    for (auto& th_game : matches) {
        th_game->stop();
        th_game->join();
        delete th_game;
    }
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

int Server::createGame(std::string& map, int min_players, int max_players, int bots, int time) {
    std::cout << "[Server] New Game created with id: " << matches.size() << "\n";
    auto new_game = new GameHandler(map, CONFIG_PATH,
                                    min_players, max_players,
                                    bots, matches.size(), time * 60);
    // pasarle game duration tambien
    new_game->start();
    matches.push_back(new_game);
    usleep(100000);
    return matches.size() - 1;
}

bool Server::joinGame(int game_id, NetworkConnection socket) {
    if (matches[game_id]->canJoinPlayer()) { // Ya esta afuera esta logica
        try {
            matches[game_id]->addNewPlayer(std::move(socket));
            std::cout << "[Server] New player connected to game " << game_id << "\n";
        } catch (const NetworkError& e) {
            return false;
        }
        usleep(100000);
        return true;
    }
    return false;
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
