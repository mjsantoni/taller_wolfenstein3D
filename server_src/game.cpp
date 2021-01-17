#include "server/game/game.h"

#include <iostream>
#include "server/game/shoot_handler.h"


#define MAX_PLAYERS 2

Game::Game(std::string map_path, std::string config_path) :
           mapParser(map_path),
           mapGenerator(mapParser, MAX_PLAYERS, config_path),
           map(mapGenerator.create()),
           colHandler(map),
           pickUpHandler(config_path),
           configParser(config_path) {

    int id1 = connectPlayer();
    int id2 = connectPlayer();
    std::cout << "Player " << id1 << " connected to game.\n";
    std::cout << "Player " << id2 << " connected to game.\n\n";
}

int Game::connectPlayer() {
    Player player(std::to_string(players_ids), players_ids,
       configParser.getSpecificCategory("player", "max_bullets"),
          configParser.getSpecificCategory("player", "max_hp"),
           configParser.getSpecificCategory("player", "bullets"));
    map.addPlayer(players_ids);
    players.push_back(player);
    players_ids++;
    players_alive++;
    return player.getID(); // return players_ids - 1;
}

Coordinate Game::movePlayer(int id) {
    Player& player = players[id];
    double angle = player.getAngle();
    Coordinate old_pos = map.getPlayerPosition(std::stoi(player.getPlayerName()));
    Coordinate new_pos = colHandler.moveToPosition(old_pos, angle);

    std::vector<std::pair<Coordinate, Positionable>> items = colHandler.getCloseItems(old_pos, new_pos);
    for (auto& item : items) {
        if(item.second.getCategory() != "wall") {
            std::cout << "################################################################\n";
            std::cout << item.second.getType() << "\n";
            if (pickUpHandler.pickUp(item.second, player)) {
                map.erasePositionableAt(item.first);
                // erased_positionables.push_back(item.first);
            }
            std::cout << "################################################################\n";
        }
    }
    map.setPlayerPosition(std::stoi(player.getPlayerName()), new_pos);
    return new_pos; // return par <nueva pos del player, vector<positionables> deleta2>
}

void Game::show() { map.show(); }

Hit Game::shoot(int id) {
    Player& shooter = players[id];
    double angle = shooter.getAngle();
    ShootHandler sh(map);
    Hit hit_event = sh.shoot(shooter, angle, players);
    if (hit_event.playerDied()) playerDies(hit_event);
    changeGun(shooter.getID(), 1); //esto pa test noma
    return hit_event;
}

void Game::rotate(int id, double angle) {
    Player& player = players[id];
    player.addAngle(angle);
}

void Game::changeGun(int id, int hotkey) {
    players[id].changeGun(hotkey);
}

bool Game::isNotOver() {
    if (players_alive <= 1) return false;
    //if (se termino el tiempo) return false;
    return true;
}

void Game::playerDies(Hit& hit) {
    // logica de quien muere y respawnearlo si fuese necesario
    players_alive--;
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
