#include "server/events/game_handler.h"

#include <unistd.h>
#include "common/network_acceptor.h"
#include "common/network_error.h"
#include "server/server.h"

#define STOP_CHAR "q"
#define ARG_PORT 1
#define ARG_AMOUNT 2

int main(int argc, char* args[]) {

    int players = std::stoi(args[1]);
    int bots = std::stoi(args[2]);
    int stop_after_seconds = std::stoi(args[3]);

    GameHandler gameHandler("../map.yaml", "../config.yaml", players, bots);
    gameHandler.start();
    NetworkAcceptor networkAcceptor("8080");

    int total_connected = 0;
    while (total_connected < players) {
        // Spawn clients
        try {
            NetworkConnection socket = std::move(networkAcceptor.acceptConnection());
            gameHandler.addNewPlayer(std::move(socket));
            total_connected++;
        } catch (const NetworkError& e) {
            continue;
        }
    }
    sleep(stop_after_seconds);
    gameHandler.stop();
    gameHandler.join();
    return 0;
}

/*
int main(int argc, char* argv[]) {
    if (argc != ARG_AMOUNT) {
        std::cerr << "[Server] Incorrect parameter amount." << std::endl;
        return 1;
    }
    const char* port = argv[ARG_PORT];

    try {
        NetworkAcceptor networkAcceptor(port);
        Server server(std::move(networkAcceptor));
        std::string buffer_stop;
        server.start();
        while (std::getline(std::cin, buffer_stop)) {
            if (buffer_stop == STOP_CHAR) break;
        }
        server.stop();
        server.join();
    } catch (const NetworkError& e) {
        std::cerr << e.what();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error." << std::endl;
    }
    return 0;
}
 */