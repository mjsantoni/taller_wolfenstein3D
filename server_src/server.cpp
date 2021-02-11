#include <algorithm>
#include "server/server.h"

Server::Server(NetworkAcceptor socket) : networkAcceptor(std::move(socket)) {
    maps.push_back("../map.yaml");
}

static bool is_null(GameHandler* gh) { return !gh; }

/* CLEAN DEAD GAMES */ // funcion q tiene berto
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

int Server::createGame(int players, int bots, int game_duration,
                        int map, NetworkConnection socket) {
    total_matches++;
    auto new_game = new GameHandler(maps[map], "../config.yaml", players, bots);
    // pasarle game duration tambien y un id
    new_game->start();
    matches.push_back(new_game);
    usleep(100000);
    return total_matches;
}

bool Server::joinGame(int game_id, NetworkConnection socket) {
    if (matches[game_id]->canJoinPlayer()) { // condicion del Game handler?
        try {
            matches[game_id]->addNewPlayer(std::move(socket));
        } catch (const NetworkError& e) {
            return false;
        }
        usleep(100000);
        return true;
    }
    return false;
}

void Server::run() {
    while (accepting_connections) {
        try {
            NetworkConnection socket = std::move(networkAcceptor.acceptConnection());
            while (true) {
                std::string buffer;
                socket.recv_msg(buffer);

                // Analizo la string para ver si crea o se joinea (tipo evento)
                int game_id = 0;
                bool create_game; // Poner el valor segun si crea o joinea
                if (create_game) game_id = createGame(0, 0, 0, 0);

                if (joinGame(game_id, std::move(socket))) break;
                // Mandar ALGO de que no pudo conectarse
                // Pedir nueva accion socket.send_msg()
                //std::string couldnt_connect("Bro no te pude conectar elegi otro lobby\n");
                //socket.send_msg(couldnt_connect);
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
