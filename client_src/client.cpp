#include "client/game/client.h"
#include <iostream>
#include <common/network_connection.h>
#include <client/communication/server_updater.h>
#include <client/game/client_game.h>


Client::Client(NetworkConnection& skt) : running(true),
                                         change_queue(Change()),
                                         event_queue(Event()),
                                         server_updater(skt, event_queue),
                                         server_listener(skt, change_queue){
}

void Client::start() {
    try {
        ClientMap map = parser.parseInfoFromServer();
        ClientGame game(change_queue, event_queue);
        server_updater.start();
        server_listener.start();
        game.startGame();
        server_updater.stop();
        server_listener.stop();
        server_updater.join();
        server_listener.join();
    }
    catch(SdlException& e) {
        std::cout << e.what() << std::endl;
    }
    running = false;
}

void Client::stop() {}

bool Client::isRunning() {
    return running;
}