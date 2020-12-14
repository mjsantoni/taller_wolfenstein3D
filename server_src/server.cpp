#include "server/server.h"
#include "server/map_generator.h"
#include "server/map_parser.h"
#include <iostream>
#include "server/player.h"

Server::Server(std::string _path) : path(_path), ch(map) {
    MapParser parser(path);
    MapGenerator generator(parser);
    map = generator.create(8); // Player max spawn count
    map.show();
    ch.setMap(map);
    map.addPlayer(0);
}

void Server::movePlayer(Player& player, double angle) {
    std::pair<int,int> old_pos = map.getPlayerPosition(std::stoi(player.getPlayerName()));
    std::pair<int,int> new_pos = ch.moveToPosition(old_pos, angle);

    std::cout << "Pos vieja: x= " << old_pos.first << " y= " << old_pos.second << "\n";
    std::cout << "Pos Nueva: x= " << new_pos.first << " y= " << new_pos.second << "\n";


    std::pair<int,int> pos_positionable(0,0);
    Positionable item = ch.getCloseItems(old_pos, new_pos, pos_positionable);
    if (!(item.getType() == "wall")) {
        std::cout << item.getId() << "\n";
        //logica del pickup
        ph.pickUp(item, player);
        map.erasePositionableAt(pos_positionable);
    }
    map.setPlayerPosition(std::stoi(player.getPlayerName()), new_pos);
}

Server::~Server() {
}
