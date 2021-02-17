#include "server/game/shoot_handler.h"
#include "server/game/coordinate.h"
#include "server/game/player.h"
#include <vector>
#include <ctgmath>
#include <cfloat>
#include "server/game/positions_calculator.h"
#include "server/game/hit.h"

#define ENEMY_DIES (-1)
#define RPG_UNITS_MOVE_PER_TURN 5
#define RPG_EXPLOSION_RADIUS 15     // esto viene del config
#define SHOOT_AMPLITUDE 10

std::pair<Hit, std::vector<Change>> ShootHandler::shoot(Player& player, double angle, std::vector<Player>& players) {
    std::vector<Change> changes; // Devuelve cambios en el mapa
    std::vector<std::pair<int,int>> enemy_dmg_done;
    int range = player.getGun().getRange();
    int bullets_to_shoot = player.getGun().getBulletsPerSpray();
    //std::cout << "Tengo tantas balas" << player.getBullets() << "\n";
    //std::cout << "Entonces el player solo peude disparar" << bullets_to_shoot << " \n";

    int x_move = std::round(cos(angle)*range);
    int y_move = std::round(sin(angle)*range*-1);
    Coordinate player_pos = map.getPlayerPosition(player.getID());
    Coordinate new_pos(player_pos.x + x_move, player_pos.y + y_move);

    PositionsCalculator ph;
    std::vector<Coordinate> straight_line = ph.straightLine(player_pos, new_pos);
    straight_line = std::vector<Coordinate>(straight_line.begin() + 1, straight_line.end());

    if (player.getGun().getType() == "rpg_gun") {
        std::pair<Hit, std::vector<Change>>
        total_changes(shootRPG(bullets_to_shoot, player, straight_line,
                               enemy_dmg_done, players, changes), changes);
        return total_changes;
    }
    if (player.getBullets() < bullets_to_shoot && player.getGun().getType() != "knife") bullets_to_shoot = player.getBullets();
    std::pair<Hit, std::vector<Change>>
    total_changes(shootRegularGun(bullets_to_shoot, player, straight_line,
                                  enemy_dmg_done, players), changes);
    return total_changes;
}

int ShootHandler::hit(Player &player, Player &enemy, int damage, bool &enemy_dies) {
    int reduced_hp = enemy.reduceHP(damage);
    enemy_dies = enemy.isDead();
    return reduced_hp;
}

Hit ShootHandler::shootRPG(int bullets_to_shoot, Player &player, std::vector<Coordinate> straight_line,
                           std::vector<std::pair<int, int>> &enemy_dmg_done, std::vector<Player> &players,
                           std::vector<Change> &changes) {
    if (player.getBullets() < bullets_to_shoot) {
        return Hit(player.getID(), 0, enemy_dmg_done, false);
    }
    scoreHandler.addBulletsShot(player.getID(), bullets_to_shoot);
    player.reduceAmmo(bullets_to_shoot);
    int new_rpg_id = map.getGlobalID();
    RPG rpg_shot(0, straight_line, player.getID(), new_rpg_id);
    travelAndExplodeRPG(rpg_shot, bullets_to_shoot, enemy_dmg_done, players);

    Coordinate current_pos(rpg_shot.getCurrentCoord());
    changes.emplace_back(RPG_MOVE_TO, rpg_shot.getRpgId(), current_pos.x, current_pos.y, true);
    if (rpg_shot.exploded()) {
        changes.emplace_back(RPG_EXPLODE_AT, rpg_shot.getRpgId(), current_pos.x, current_pos.y, true);
    } else {
        rpgs.insert(std::make_pair(new_rpg_id, rpg_shot));
    }

    return Hit(player.getID(), bullets_to_shoot, enemy_dmg_done, player.noAmmoLeft());
}

Hit ShootHandler::travelAndExplodeAllRPGS(std::vector<Player> &players, std::vector<Change> &changes) {
    std::vector<std::pair<int, int>> enemy_dmg_done;
    std::vector<int> exploded_rpgs;
    for (auto& rpg_item : rpgs) {
        RPG& rpg = rpg_item.second;
        Coordinate previous_pos(rpg.getCurrentCoord());
        travelAndExplodeRPG(rpg, 0, enemy_dmg_done, players);
        Coordinate current_pos(rpg.getCurrentCoord());

        map.erasePositionableAt(previous_pos);
        if (rpg.exploded()) {
            exploded_rpgs.push_back(rpg.getRpgId());
            changes.emplace_back(RPG_EXPLODE_AT, rpg.getRpgId(), current_pos.x, current_pos.y, true);
        } else {
            changes.emplace_back(RPG_MOVE_TO, rpg.getRpgId(), current_pos.x, current_pos.y, true);
        }
    }

    for (auto& rpg_id : exploded_rpgs) {
        rpgs.erase(rpg_id);
    }

    return Hit(-1, 0, enemy_dmg_done, false);
}

Hit ShootHandler::travelAndExplodeRPG(RPG &rpg, int bullets_to_shoot,
                                      std::vector<std::pair<int, int>> &enemy_dmg_done,
                                      std::vector<Player> &players) {
    std::vector<Coordinate>& rpg_path = rpg.getPath();
    int position = rpg.getCurrentPosition();
    Player& player = players[rpg.getPlayerId()];
    int end_pos = position + RPG_UNITS_MOVE_PER_TURN;
    for (; (position < rpg_path.size() - 1) && (position < end_pos); position++) {
        //std::cout << "Current pos " << position << " - "; rpg_path[position].show();

        std::vector<int> players_found = playersInArea(rpg_path[position], RPG_EXPLOSION_RADIUS, rpg.getPlayerId());
        if (map.isABlockingItemAt(rpg_path[position]) || !players_found.empty()) {
            //std::cout << "Encontre alguien en la position " << position << "\n";
            hitPlayersWithRPG(players_found, player, rpg_path[position], enemy_dmg_done, players);
            rpg.explode();
            break;
        }
    }
    if (position == (rpg_path.size() - 1) && !rpg.exploded()) {
        std::vector<int> players_found = playersInArea(rpg_path[position], RPG_EXPLOSION_RADIUS, rpg.getPlayerId());
        hitPlayersWithRPG(players_found, player, rpg_path[position], enemy_dmg_done, players);
        rpg.explode();
    }
    rpg.setCurrentPosition(position);
    rpg.setCurrentCoordinate(rpg_path[position]);
    return Hit(-1, bullets_to_shoot, enemy_dmg_done, false);
}

void ShootHandler::hitPlayersWithRPG(std::vector<int> &players_found, Player &player, Coordinate explosion_center,
                                     std::vector<std::pair<int, int>> &enemy_dmg_done, std::vector<Player> &players) {
    int damage = player.getGun().getDamage();
    for (auto& player_id : players_found) {
        Player& enemy = players[player_id];
        bool enemy_dies = false;
        Coordinate player_hit_position = map.getPlayerPosition(player_id);
        //std::cout << "----------------\n";
        //std::cout << "Shoot de RPG con (daño random): " << damage << "\n";
        //std::cout << "Le va a pegar a Player " << player_id << "\n";
        int final_damage = dmg_calculator.calculateDamageRPG(player, damage, explosion_center,
                                                             player_hit_position, RPG_EXPLOSION_RADIUS);
        int damage_done = hit(player, enemy, final_damage, enemy_dies);
        enemy_dmg_done.emplace_back(player_id, damage_done);
        if (enemy_dies) enemy_dmg_done.emplace_back(enemy.getID(), ENEMY_DIES);
    }
}

std::vector<int> ShootHandler::playersInArea(Coordinate& coord, int units, int id) {
    std::vector<int> players_found;
    for (int i = coord.x-units; i <= coord.x+units; i++) {
        for (int j = coord.y-units; j <= coord.y+units; j++) {
            Coordinate pos(i,j);
            if (map.isAPlayerAt(pos) && map.getPlayerIDAtPosition(pos) != id) {
                //std::cout << "Encontre en el area cercana a player: " << map.getPlayerIDAtPosition(pos) << "\n";
                players_found.push_back(map.getPlayerIDAtPosition(pos));
            }
        }
    }
    return players_found;
}


Hit ShootHandler::shootRegularGun(int bullets_to_shoot, Player& player,
                                  std::vector<Coordinate>& straight_line,
                                  std::vector<std::pair<int,int>>& enemy_dmg_done,
                                  std::vector<Player>& players) {
    double angle = player.getAngle();
    bool wall_at_pos = false;
    int bullets_shot = 0;
    for (; bullets_shot < bullets_to_shoot; bullets_shot++) {
        int pos_travelled = 1;
        if (wall_at_pos) continue;
        for (auto& pos : straight_line) {
            if (map.isABlockingItemAt(pos)) {
                wall_at_pos = true;
                break;
            }
            std::vector<Coordinate> center_pos; center_pos.push_back(pos);
            std::vector<Coordinate> adj = getAdjacents(pos, angle, SHOOT_AMPLITUDE);
            if (hitAtPos(center_pos, players, player, enemy_dmg_done, pos_travelled, false) ||
                hitAtPos(adj, players, player, enemy_dmg_done, pos_travelled, true)) {
                break;
            }
            pos_travelled++;
        }
    }
    if (player.getGun().getType() == "knife") bullets_shot = 0;
    player.reduceAmmo(bullets_shot);
    scoreHandler.addBulletsShot(player.getID(), bullets_shot);
    return Hit(player.getID(), bullets_shot, enemy_dmg_done, player.noAmmoLeft());
}

bool ShootHandler::hitAtPos(std::vector<Coordinate>& positions, std::vector<Player> &players, Player &player,
                            std::vector<std::pair<int, int>> &enemy_dmg_done, int pos_travelled,
                            bool is_adjacent) {
    for (auto& pos : positions) {
        if (!map.isAPlayerAt(pos)) continue;
        Player &enemy = players[map.getPlayerIDAtPosition(pos)];
        if (enemy.isDead()) continue;
        int damage = player.getGun().getDamage();
        bool enemy_dies = false;
        //std::cout << "----------------\n";
        //std::cout << "Nuevo tiro, intento shootear con (daño random): " << damage << "\n";
        damage = dmg_calculator.calculateDmg(player, damage, pos_travelled, is_adjacent);
        int damage_done = hit(player, enemy, damage, enemy_dies);
        enemy_dmg_done.emplace_back(enemy.getID(), damage_done);
        if (enemy_dies) enemy_dmg_done.emplace_back(enemy.getID(), ENEMY_DIES);
        return true;
    }
    return false;
}

std::vector<Coordinate> ShootHandler::getAdjacents(Coordinate &pos, double angle, int adj_units_to_check) {
    std::pair<Coordinate, Coordinate> adj;
    std::vector<Coordinate> adjacents;
    if ((0 < angle && angle < M_PI/2 && std::abs(angle - M_PI/2) > DBL_EPSILON
                                     && std::abs(angle - 0) > DBL_EPSILON) ||
    (M_PI < angle && angle < 3*M_PI/2 && std::abs(angle - M_PI) > DBL_EPSILON
                                      && std::abs(angle - 3*M_PI/2) > DBL_EPSILON)) {
        for (int i = 1; i <= adj_units_to_check; ++i) {
            adjacents.emplace_back(pos.x - i, pos.y - i);
            adjacents.emplace_back(pos.x + i, pos.y + i);
        }
    } else if ((std::abs(angle - M_PI/2) < DBL_EPSILON) ||
               (std::abs(angle - 3*M_PI/2) < DBL_EPSILON)) {
        for (int i = 1; i <= adj_units_to_check; ++i) {
            adjacents.emplace_back(pos.x - i, pos.y);
            adjacents.emplace_back(pos.x + i, pos.y);
        }
    } else if ((M_PI/2 < angle && angle < M_PI && std::abs(angle - M_PI/2) > DBL_EPSILON
                                               && std::abs(angle - M_PI) > DBL_EPSILON) ||
            (3*M_PI/2 < angle && angle < 2*M_PI && std::abs(angle - 3*M_PI/2) > DBL_EPSILON
                                                && std::abs(angle - 2*M_PI) > DBL_EPSILON)){
        for (int i = 1; i <= adj_units_to_check; ++i) {
            adjacents.emplace_back(pos.x - i, pos.y + i);
            adjacents.emplace_back(pos.x + i, pos.y - i);
        }
    } else if ((std::abs(angle - M_PI) < DBL_EPSILON) ||
               (std::abs(angle - 0) < DBL_EPSILON) ||
               (std::abs(angle - 2*M_PI) < DBL_EPSILON)) {
        for (int i = 1; i <= adj_units_to_check; ++i) {
            adjacents.emplace_back(pos.x, pos.y - i);
            adjacents.emplace_back(pos.x, pos.y + i);
        }
    } else { std::cout << "No hay ninguna posicion alrededor, algo raro paso.\n"; }
    return adjacents;
}
