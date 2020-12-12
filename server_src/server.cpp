#include "server/server.h"
#include "server/map_generator.h"
#include "server/map_parser.h"
#include "server/map.h"
#include "server/colission_handler.h"
#include <iostream>

Server::Server(std::string _path) : path(_path) {
    MapParser parser(path);
    MapGenerator generator(parser);
    Map map = generator.create(8); // Player max spawn count
    //map.show();
    ColissionHandler colHandler(map);
/*
    for (int i = 74; i < 100; i++) {
        std::pair<int,int> test(i,i);
        test = colHandler.moveToPosition(test, (3*M_PI)/4);
        std::cout << "Par: " << i << " - (" << test.first << ", " << test.second << ")\n";
    }*/

    std::pair<int,int> test(73,73);
    test = colHandler.moveToPosition(test, 3*M_PI/4);
    std::cout << test.first << " " << test.second;





}

Server::~Server() {
}
