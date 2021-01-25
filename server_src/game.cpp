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
           dropHandler(config_path, map),
           blockingItemHandler(map) {

    //int id1 = connectPlayer();
    //int id2 = connectPlayer();
    //std::cout << "Player " << id1 << " connected to game.\n";
    //std::cout << "Player " << id2 << " connected to game.\n\n";
    //players[id2].addKey(Key(50)); // TEST ONLY
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
    std::cout << "Player " << player.getID() << " connected to game.\n";
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
        if(item.second.getCategory() != "wall") { // Este if no es necesario
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
    return true;
    if (players_alive <= 1) return false;
    //if (se termino el tiempo) return false;
    return true;
}

void Game::playerDies(Hit& hit) {
    std::vector<std::pair<int, bool>> dead_respawn_players; //(id, muere y respawnea o no) (para clientes)
    for (auto& dead_player : hit.getDeadPlayers()) {
        if (players[dead_player].dieAndRespawn()) {
            std::pair<std::string, bool> drops = players[dead_player].getDrops();
            addDropsToHitEvent(drops, hit, map.getPlayerPosition(dead_player));
            // carga todos los drops de la muerte del player enemigo para enviar a clientes

            map.respawnPlayer(dead_player); // respawnea en el sv
            dead_respawn_players.emplace_back(dead_player, true);
        }
        else {
            map.removePlayer(dead_player); // le pone pos = -1,-1 en el sv
            players_alive--;
            dead_respawn_players.emplace_back(dead_player, false);
        }
    }
    dropHandler.processDrops(hit.getDrops());
    // carga en el mapa del sv esos drops

    hit.setPlayersDeaths(dead_respawn_players);
}

void Game::addBulletsTo(int id, int bullets) { // SOLO PARA TEST
    players[id].addBullets(bullets);
}

void Game::addDropsToHitEvent(const std::pair<std::string, bool> &drops,
                              Hit &hit, const Coordinate& pos) {
    if (drops.first != "pistol") {
        Coordinate gun_pos(pos.x, pos.y - 2);
        hit.addDrops(drops.first, gun_pos, map.getGlobalID(), GUN);
    }
    if (drops.second) {
        Coordinate key_pos(pos.x, pos.y + 2);
        hit.addDrops("key", key_pos, map.getGlobalID(), KEY);
    }
    Coordinate bullets_pos(pos.x + 2, pos.y);
    hit.addDrops("bullets", bullets_pos, map.getGlobalID(), BULLETS);
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

std::pair<Coordinate, int> Game::openDoor(int id) {
    Coordinate door_to_open = colHandler.getCloseBlocking(map.getPlayerPosition(id),
                                                          players[id].getAngle(), "door");
    Coordinate not_opened(-1, -1);
    if (!door_to_open.isValid()) return std::make_pair(not_opened, -1);

    std::pair<bool, int> opened_door = blockingItemHandler.openDoor(door_to_open, players[id]);
    if (!opened_door.first) return std::make_pair(not_opened, opened_door.second);
    std::cout << "Abro una puerta con llave id: " << opened_door.second << " en ";
    map.getNormalizedCoordinate(door_to_open).show();

    return std::make_pair(map.getNormalizedCoordinate(door_to_open),
                          opened_door.second);
}

Coordinate Game::pushWall(int id) {
    Coordinate wall_to_push = colHandler.getCloseBlocking(map.getPlayerPosition(id),
                                                          players[id].getAngle(), "wall");
    Coordinate not_pushed(-1, -1);
    if (!wall_to_push.isValid()) return not_pushed;
    if (!blockingItemHandler.pushWall(wall_to_push)) return not_pushed;
    return map.getNormalizedCoordinate(wall_to_push);
}

std::pair<Coordinate, int> Game::closeDoor() {
    return blockingItemHandler.closeDoor();
}





