#include <algorithm>
#include "server/server.h"

Server::Server(NetworkAcceptor socket) :
        networkAcceptor(std::move(socket)),
        accepting_connections(true) {
    maps.emplace_back("../map.yaml");
}

#define CREATE_GAME "0"
#define JOIN_GAME "1"
#define SUCCESS "2"
#define ERROR "3"

void Server::run() {
    //std::string name = "map.yaml";
    //createGame(name, 1, 5, 0,10);
    //createGame(name, 1, 5, 0,10);
    //createGame(name, 1, 5, 0,10);
    //createGame(name, 1, 5, 0,10);
    //createGame(name, 1, 5, 0,10);
    //createGame(name, 1, 5, 0,10);
    std::cout << "[Server] Started.\n";
    while (accepting_connections) {
        try {
            NetworkConnection socket = std::move(networkAcceptor.acceptConnection());
            std::string player_choice;
            socket.recv_msg(player_choice); // Recibo el tipo de evento
            //std::cout << "Recibi tal opcion: " << player_choice << "\n";
            while (true) {
                if (player_choice == CREATE_GAME) {
                    std::string options;
                    socket.recv_msg(options);
                    std::cout << "Me paso estas opciones: " << options << "\n";
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
                    //socket.send_msg(std::to_string(matches.size())); // envio cant de games disponibles
                    sendGames(socket);

                    std::string game_choice;
                    socket.recv_msg(game_choice);

                    int game_id_to_connect = std::stoi(game_choice);
                    // id -> tiene que ser de 0 a n por indices del vector. LP pasarlo bien
                    std::cout << "El player se quiere unir al game: " << game_choice << "\n";

                    if (game_id_to_connect > (matches.size() - 1) || game_id_to_connect < 0) {
                        socket.send_msg("No podes errarle tanto pa\n");
                        continue;
                    } else {
                        if(!joinGame(game_id_to_connect, std::move(socket))) {
                            std::string couldnt_connect("Bro no te pude conectar elegi otro lobby\n");
                            socket.send_msg(couldnt_connect);
                        } else {
                            socket.send_msg("1\n");
                            joinGame(game_id_to_connect, std::move(socket));
                        }
                        break;
                    }
                }
            }
        } catch (const NetworkError& e) {
            continue;
        }

        // Kill ended games
        killDead();
        usleep(100000);
    }

    for (auto& th_game : matches) {
        th_game->join();
        delete th_game;
    }
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
    auto new_game = new GameHandler(map, "../config.yaml",
                                    min_players, max_players,
                                    bots, matches.size(), time * 60);
    // pasarle game duration tambien
    new_game->start();
    matches.push_back(new_game);
    usleep(100000);
    return matches.size() - 1;
}

bool Server::joinGame(int game_id, NetworkConnection socket) {
    if (matches[game_id]->canJoinPlayer()) {
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
        std::string name();
        socket.send_msg(game->getInformation());
    }
    socket.send_msg(SUCCESS);
}

void Server::stop() {
    accepting_connections = false;
    networkAcceptor.closeSocket();
}

Server::~Server() {}
