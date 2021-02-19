#include <algorithm>
#include "server/server.h"

Server::Server(NetworkAcceptor socket) :
        networkAcceptor(std::move(socket)),
        accepting_connections(true) {
    maps.emplace_back("../map.yaml");
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

int Server::createGame(int max_players, int bots, int game_duration,
                       int map, int min_players_in_lobby) {
    std::cout << "[Server] New Game created with id: " << matches.size() << "\n";
    auto new_game = new GameHandler(maps[map], "../config.yaml",
                                    min_players_in_lobby, max_players,
                                    bots, matches.size(), game_duration);
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

#define CREATE_GAME "0"
#define JOIN_GAME "1"

void Server::run() {
    std::cout << "[Server] Started.\n";
    while (accepting_connections) {
        try {
            NetworkConnection socket = std::move(networkAcceptor.acceptConnection());
            std::string player_choice;
            socket.recv_msg(player_choice); // Recibo el tipo de evento
            std::cout << "Recibi tal opcion: " << player_choice << "\n";
            // Aca LP verifica que sea 1 o 0 sino ni lo manda porq no deberiamos revisar eso
            while (true) {
                if (player_choice == CREATE_GAME) {
                    std::string options;
                    socket.recv_msg(options);
                    std::cout << "Me paso estas opciones: " << options << "\n";
                    std::vector<int> game_options = split(options); // players/bots/duration/map_id
                    if (game_options.size() > 4 || game_options.size() < 4) { //ACA VALIDAR LOS PARAMETROS
                        socket.send_msg("?????\n");
                        continue;
                    } else {
                        socket.send_msg("1\n"); // created
                        int new_game_id = createGame(game_options[0], game_options[1], game_options[2], game_options[3],
                                                     0);
                        joinGame(new_game_id, std::move(socket));
                        break;
                    }
                } else {
                    socket.send_msg(std::to_string(matches.size())); // envio cant de games disponibles
                    std::string game_choice;
                    socket.recv_msg(game_choice);
                    // game_id -> tiene que ser de 0 a n por indices del vector. LP pasarlo bien
                    std::cout << "El player se quiere unir al game: " << game_choice << "\n";

                    int game_id_to_connect;
                    try { game_id_to_connect = std::stoi(game_choice); }
                    catch (const std::invalid_argument& e) {
                        socket.send_msg("Tenes que apretar un numero pa\n");
                        continue;
                    }

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

void Server::stop() {
    accepting_connections = false;
    networkAcceptor.closeSocket();
}

Server::~Server() {}
