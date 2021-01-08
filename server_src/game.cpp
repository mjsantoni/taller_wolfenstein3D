#include "server/game/game.h"
#include "server/game/map_generator.h"
#include "server/game/map_parser.h"
#include <iostream>
#include "server/game/shoot_handler.h"
#include "server/game/player.h"

Game::Game(std::string _path) : path(_path), ch(map) {
    MapParser parser(path);
    MapGenerator generator(parser);
    map = generator.create(2); // Player max spawn count
    Player p1("0",0);
    Player p2("1",1);
    ch.setMap(map);
    map.addPlayer(0);
    map.addPlayer(1);
    players.push_back(p1);
    players.push_back(p2);
    //map.show();
}

void Game::movePlayer(int id, double angle) {
    Player player = players[id];
    Coordinate old_pos = map.getPlayerPosition(std::stoi(player.getPlayerName()));
    Coordinate new_pos = ch.moveToPosition(old_pos, angle);
    //std::cout << "Old: x: " << old_pos.x << " - y: " << old_pos.y << "\n";
    //std::cout << "New: x: " << new_pos.x << " - y: " << new_pos.y << "\n";

    Coordinate pos_positionable(0,0);
    Positionable item = ch.getCloseItems(old_pos, new_pos, pos_positionable);
    // falta que haga el get close items desde la pos q encontro el objeto hasta
    // la nueva pos final final, porq si encuentra en el medio del camino
    // corta el camino ahi y aparece en la nueva pos
    if (!(item.getCategory() == "wall")) {
        std::cout << "################################################################\n";
        std::cout << item.getType() << "\n";
        ph.pickUp(item, player);
        map.erasePositionableAt(pos_positionable);
        std::cout << "################################################################\n";
    }
    map.setPlayerPosition(std::stoi(player.getPlayerName()), new_pos);

}
void Game::show() { map.show();}

void Game::shoot(int id, double angle) {
    Player player = players[id];
    ShootHandler sh(map);
    sh.shoot(player,angle,players);
}

Game::~Game() {}
