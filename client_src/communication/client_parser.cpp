//
// Created by andy on 10/12/20.
//

#include "client/client_parser.h"

ClientMap ClientParser::parseInfoFromServer() {
    ClientMap map(15, 20, 64);
    std::vector<std::pair<int, int>> walls = createWalls(15, 20);
    std::vector<int> types = createTypes(15,20);
    map.addWalls(walls, types);
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

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height-2; ++j) {
            if (i == 3*width/4)
                vector.emplace_back(i,j);
        }
    }

    return vector;
}

std::vector<int> ClientParser::createTypes(int width, int height) {
    std::vector<int> vector;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (i == 0 || i == width-1 || j == 0 || j == height-1)
                vector.push_back(0);
        }
    }

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height-2; ++j) {
            if (i == width/2)
                vector.push_back(1);
        }
    }

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height-2; ++j) {
            if (i == 3*width/4)
                vector.push_back(2);
        }
    }

    return vector;
}
