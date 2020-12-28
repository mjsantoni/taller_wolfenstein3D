//
// Created by andy on 10/12/20.
//

#include "client/client_parser.h"

ClientMap ClientParser::parseInfoFromServer() {
    ClientMap map(15, 20, 64);
    std::vector<std::pair<int, int>> walls = createWalls(15, 20);
    map.addWalls(walls);
    return map;
}

std::vector<std::pair<int, int>> ClientParser::createWalls(int width,
                                                           int height) {
    std::vector<std::pair<int, int>> vector;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (i == 0 || i == width-1 || j == 0 || j == height-1)
                vector.emplace_back(i,j);
        }
    }

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height-2; ++j) {
            if (i == width/2)
                vector.emplace_back(i,j);
        }
    }
    return vector;
}
