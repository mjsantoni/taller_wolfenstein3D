#include "client/client.h"
#include "client/client_game.h"
#include <iostream>

Client::Client(int width, int height, std::vector<std::pair<int,int>>& _walls) :
                map_width(width), map_height(height), walls(_walls) {
}

void Client::run() {
    try {
        ClientGame game(960, 600, map_width, map_height);
        game.start(walls);
    }
    catch(SdlException& e) {
        std::cout << e.what() << std::endl;
        return;
    }
}

Client::~Client() {}