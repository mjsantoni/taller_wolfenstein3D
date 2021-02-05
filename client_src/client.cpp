#include "client/game/client.h"
#include <iostream>
#include <common/network_connection.h>
#include <client/communication/server_updater.h>


Client::Client(NetworkConnection& skt) : running(true), updater(skt, 1) {
}



void Client::run() {
    try {
        ClientMap map = parser.parseInfoFromServer();
        MapMock real_map(15, 20);
        ClientGame game(960, 600, real_map, map, updater);
        updater.start();
        game.start();
    }
    catch(SdlException& e) {
        std::cout << e.what() << std::endl;
    }
    running = false;
}

Client::~Client() {}

void Client::stop() {}

bool Client::isRunning() {
    return running;
}