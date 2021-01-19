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
           configParser(config_path),
           dropHandler(config_path) {

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

std::pair<Coordinate, std::vector<Positionable>> Game::movePlayer(int id) {
    std::vector<Positionable> erased_positionables;
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
                erased_positionables.push_back(item.second);
            }
            std::cout << "################################################################\n";
        }
    }
    map.setPlayerPosition(player.getID(), new_pos);
    return std::make_pair(new_pos, erased_positionables);
}

void Game::show() { map.show(); }

Hit Game::shoot(int id) {
    Player& shooter = players[id];
    double angle = shooter.getAngle();
    ShootHandler sh(map);
    Hit hit_event = sh.shoot(shooter, angle, players);
    if (hit_event.playerDied()) playerDies(hit_event);
    hit_event.getEnemyDmgDone(2); //TEST USE
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
    std::vector<std::pair<int, bool>> dead_respawn_players;
    for (auto& dead_player : hit.getDeadPlayers()) {
        if (players[dead_player].dieAndRespawn()) {
            std::pair<std::pair<std::string, int>, int>
                    drops = players[dead_player].getDrops();
            addDropsToHitEvent(drops, hit, map.getPlayerPosition(dead_player));
            dropPlayerItems(drops,
                            map.getPlayerPosition(dead_player));
            respawnPlayer(dead_player);
            dead_respawn_players.emplace_back(dead_player, true);
        }
        else {
            killPlayerDefinitely(dead_player);
            players_alive--;
            dead_respawn_players.emplace_back(dead_player, false);
        }
    }
    hit.setPlayerRespawns(dead_respawn_players);
}

void Game::dropPlayerItems(const std::pair<std::pair<std::string, int>, int>& drops,
                           const Coordinate& coordinate) {
    dropHandler.processDrops(drops, map, coordinate);
}

void Game::respawnPlayer(int& player) {
    map.respawnPlayer(player);
}

void Game::killPlayerDefinitely(int &player) {
    map.removePlayer(player);
}

void Game::addBulletsTo(int id, int bullets) { // SOLO PARA TEST
    players[id].addBullets(bullets);
}

void Game::addDropsToHitEvent(const std::pair<std::pair<std::string, int>, int>& drops,
                              Hit &hit, const Coordinate& pos) {
    if (drops.first.second != -1) {
        Coordinate gun_pos(pos.x, pos.y - 2);
        hit.addDrops(drops.first.second, gun_pos);
    }
    if (drops.second != -1) {
        Coordinate key_pos(pos.x, pos.y + 2);
        hit.addDrops(drops.second, key_pos);
    }
    Coordinate bullets_pos(pos.x + 2, pos.y);
    hit.addDrops(-1, bullets_pos);
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





