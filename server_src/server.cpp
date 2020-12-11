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
    std::pair<int,int> test(80,80);
    test = colHandler.moveToPosition(test, M_PI/2);
    std::cout << test.first << " " << test.second;
}

Server::~Server() {
}
