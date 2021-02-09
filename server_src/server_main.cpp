#include "server/events/game_handler.h"

#include <unistd.h>
#include "common/network_acceptor.h"
#include "common/network_error.h"

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
