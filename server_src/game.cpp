#include "server/game/game.h"

#include <iostream>
#include "server/game/shoot_handler.h"


#define MAX_PLAYERS 2

Game::Game(std::string map_path, std::string config_path) :
           mapParser(map_path),
           mapGenerator(mapParser, MAX_PLAYERS, config_path),
           map(mapGenerator.create()),
           colHandler(map),
           pickUpHandler(config_path) {

    Player p1("0",0);
    Player p2("1",1);
    map.addPlayer(0);
    map.addPlayer(1);
    players.push_back(p1);
    players.push_back(p2);
    //map.show();
}

int Game::connectPlayer() {
    Player player(std::to_string(players_ids), players_ids);
    map.addPlayer(players_ids);
    players.push_back(player);
    players_ids++;
    return player.getID(); // return players_ids - 1;
}

Coordinate Game::movePlayer(int id, double angle) {
    Player& player = players[id];
    Coordinate old_pos = map.getPlayerPosition(std::stoi(player.getPlayerName()));
    Coordinate new_pos = colHandler.moveToPosition(old_pos, angle);

    std::vector<std::pair<Coordinate, Positionable>> items = colHandler.getCloseItems(old_pos, new_pos);
    for (auto& item : items) {
        if(item.second.getCategory() != "wall") {
            std::cout << "################################################################\n";
            std::cout << item.second.getType() << "\n";
            pickUpHandler.pickUp(item.second, player);
            map.erasePositionableAt(item.first);
            std::cout << "################################################################\n";
        }
    }
    map.setPlayerPosition(std::stoi(player.getPlayerName()), new_pos);
    return new_pos;
}

void Game::show() { map.show(); }

void Game::shoot(int id, double angle) {
    Player& shooter = players[id];
    ShootHandler sh(map);
    sh.shoot(shooter,angle,players);
    shooter.changeGun(1);
}

/*
void Game::passTime() {
    if (map.isARPGMoving()) {
        map.moveRpg();
        events.push(Event(REMOV,......))
    }
}
*/

Game::~Game() {}
