#include "client/client.h"
#include "client/client_game.h"
#include <iostream>

Client::Client() : running(true) {}

void Client::run() {
    try {
        ClientMap map = parser.parseInfoFromServer();
        MapMock real_map(10, 20);
        ClientGame game(960, 600, map, real_map);
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