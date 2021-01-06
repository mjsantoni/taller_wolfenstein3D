#include "server/game.h"
#include "server/map_generator.h"
#include "server/map_parser.h"
#include <iostream>
#include "server/player.h"

Game::Game(std::string _path) : path(_path), ch(map) {
    MapParser parser(path);
    MapGenerator generator(parser);
    map = generator.create(8); // Player max spawn count
    ch.setMap(map);
    map.addPlayer(0);
    map.show();
}

void Game::movePlayer(Player& player, double angle) {
    Coordinate old_pos = map.getPlayerPosition(std::stoi(player.getPlayerName()));
    Coordinate new_pos = ch.moveToPosition(old_pos, angle);
    std::cout << "Old: x: " << old_pos.x << " - y: " << old_pos.y << "\n";
    std::cout << "New: x: " << new_pos.x << " - y: " << new_pos.y << "\n";

    Coordinate pos_positionable(0,0);
    Positionable item = ch.getCloseItems(old_pos, new_pos, pos_positionable);
    // falta que haga el get close items desde la pos q encontro el objeto hasta
    // la nueva pos final final, porq si encuentra en el medio del camino
    // corta el camino ahi y aparece en la nueva pos

    if (!(item.getType() == "wall")) {
        std::cout << "################################################################\n";
        std::cout << item.getId() << "\n";
        ph.pickUp(item, player);
        map.erasePositionableAt(pos_positionable);
        std::cout << "################################################################\n";
    }
    map.setPlayerPosition(std::stoi(player.getPlayerName()), new_pos);

}
void Game::show() { map.show();}


Game::~Game() {}
