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

    std::pair<int,int> start(122,122);
    std::cout << "Muevo de: (" << start.first << ", " << start.second << ")\n";
    std::pair<int,int> end = colHandler.moveToPosition(start, 3*M_PI/8);
    std::cout << "Hasta: (" << end.first << ", " << end.second << ")\n";

    std::pair<int,int> pos1(120,120);
    std::pair<int,int> pos2(130,130);
    Positionable item = colHandler.getCloseItems(pos1, pos2);
    if (!(item.getType() == "wood_wall")) {
        std::cout << item.getType() << "\n";
        //logica del pickup
        //player.pickup(item)
        //map.erasePositionableAt(pos)
    }
    //no pickupear nada

}

Server::~Server() {
}
