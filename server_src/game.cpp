#include "server/game.h"
#include "server/map_generator.h"
#include "server/map_parser.h"
#include <iostream>
#include "server/player.h"

Game::Game(std::string _path) : path(_path), ch(map) {
    MapParser parser(path);
    MapGenerator generator(parser);
    map = generator.create(8); // Player max spawn count
    map.show();
    ch.setMap(map);
    map.addPlayer(0);
}

void Game::movePlayer(Player& player, double angle) {
    std::pair<int,int> old_pos = map.getPlayerPosition(std::stoi(player.getPlayerName()));
    std::pair<int,int> new_pos = ch.moveToPosition(old_pos, angle);

    std::pair<int,int> pos_positionable(0,0);
    Positionable item = ch.getCloseItems(old_pos, new_pos, pos_positionable);
    if (!(item.getType() == "wall")) {
        std::cout << item.getId() << "\n";
        ph.pickUp(item, player);
        map.erasePositionableAt(pos_positionable);
    }
    map.setPlayerPosition(std::stoi(player.getPlayerName()), new_pos);
}

Game::~Game() {}
