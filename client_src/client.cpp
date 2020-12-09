//
// Created by ubuntu on 9/12/20.
//

#include "client/client.h"
#include "client/game.h"
#include <iostream>

Client::Client(int width, int height, std::vector<std::pair<int,int>> walls) {
    try {
        Game game(960, 600, width, height);
        game.start(walls);
    }
    catch(SdlException& e) {
        std::cout << e.what() << std::endl;
        return;
    }
}
