#include "server/game/shoot_handler.h"
#include "server/game/coordinate.h"
#include "server/game/player.h"
#include <vector>
#include <ctgmath>
#include "server/game/positions_calculator.h"
#include "server/game/hit.h"
#include "server/game/damage_calculator.h"
#include <cfloat>

#define ENEMY_DIES (-1)

Hit ShootHandler::shoot(Player& player, double angle, std::vector<Player>& players) {
    std::vector<std::pair<int,int>> enemy_dmg_done;
    int range = player.getGun().getRange();
    int bullets_to_shoot = player.getGun().getBulletsPerSpray();
    bool wall_at_pos = false;
    int x_move = std::round(cos(angle)*range);
    int y_move = std::round(sin(angle)*range*-1);
    Coordinate player_pos = map.getPlayerPosition(player.getID());
    Coordinate new_pos(player_pos.x + x_move, player_pos.y + y_move);

    PositionsCalculator ph;
    std::vector<Coordinate> straight_line = ph.straightLine(player_pos, new_pos);
    straight_line = std::vector<Coordinate>(straight_line.begin() + 1, straight_line.end());
    int bullets_shot = 0;
    for (; bullets_shot < bullets_to_shoot; bullets_shot++) {
        int pos_travelled = 1;
        std::cout << "Shooteo bala nro " << bullets_shot << "\n";
        if (wall_at_pos || player.noAmmoLeft()) break;
        for (auto& pos : straight_line) {
            if (map.isABlockingItemAt(pos)) {
                wall_at_pos = true;
                break;
            }
            std::pair<Coordinate, Coordinate> adj = getAdjacents(pos, angle);
            if (hitAtPos(pos, players, player, enemy_dmg_done, pos_travelled, false) ||
                hitAtPos(adj.first, players, player, enemy_dmg_done, pos_travelled, true) ||
                hitAtPos(adj.second, players, player, enemy_dmg_done, pos_travelled, true)) {
                break;
            }
            pos_travelled++;
        }
    }
    if (wall_at_pos) return Hit(player.getID(), bullets_shot, enemy_dmg_done, false);
    if (player.noAmmoLeft()) {
        std::cout << "No ammo left aviso\n";
        return Hit(player.getID(), bullets_shot, enemy_dmg_done, true);
    } else {
        return Hit(player.getID(), bullets_shot, enemy_dmg_done, false);
    }
}

int ShootHandler::hit(Player &player, Player &enemy, int damage, bool &enemy_dies) {
    player.reduceAmmo();
    int reduced_hp = enemy.reduceHP(damage);
    enemy_dies = enemy.isDead();
    return reduced_hp;
}

bool ShootHandler::hitAtPos(Coordinate &pos, std::vector<Player> &players, Player &player,
                            std::vector<std::pair<int, int>> &enemy_dmg_done, int pos_travelled,
                            bool is_adjacent) {
    if (!map.isAPlayerAt(pos)) return false;
    Player& enemy = players[map.getPlayerIDAtPosition(pos)];
    if (enemy.isDead()) {
        std::cout << "El enemigo ha muerto, no le hago mas daño y busco otro\n";
        return false;
    }
    int damage = player.getGun().getDamage();
    bool enemy_dies = false;
    std::cout << "----------------\n";
    std::cout << "Nuevo tiro, intento shootear con (daño random): " << damage << "\n";
    DamageCalculator dmg_calculator;
    damage = dmg_calculator.calculate_dmg(player, damage, pos_travelled, is_adjacent);
    int damage_done = hit(player, enemy, damage, enemy_dies);

    enemy_dmg_done.emplace_back(enemy.getID(), damage_done);
    if (enemy_dies) enemy_dmg_done.emplace_back(enemy.getID(), ENEMY_DIES);
    return true;
}

std::pair<Coordinate, Coordinate> ShootHandler::getAdjacents(Coordinate& pos, double angle) {
    std::pair<Coordinate, Coordinate> adj;
    if ((0 < angle && angle < M_PI/2 && std::abs(angle - M_PI/2) > DBL_EPSILON
                                     && std::abs(angle - 0) > DBL_EPSILON) ||
    (M_PI < angle && angle < 3*M_PI/2 && std::abs(angle - M_PI) > DBL_EPSILON
                                      && std::abs(angle - 3*M_PI/2) > DBL_EPSILON)) {
        adj.first = Coordinate(pos.x - 1, pos.y - 1);
        adj.second = Coordinate(pos.x + 1, pos.y + 1);
    } else if ((std::abs(angle - M_PI/2) < DBL_EPSILON) ||
               (std::abs(angle - 3*M_PI/2) < DBL_EPSILON)) {
        adj.first = Coordinate(pos.x - 1, pos.y);
        adj.second = Coordinate(pos.x + 1, pos.y);
    } else if ((M_PI/2 < angle && angle < M_PI && std::abs(angle - M_PI/2) > DBL_EPSILON
                                               && std::abs(angle - M_PI) > DBL_EPSILON) ||
            (3*M_PI/2 < angle && angle < 2*M_PI && std::abs(angle - 3*M_PI/2) > DBL_EPSILON
                                                && std::abs(angle - 2*M_PI) > DBL_EPSILON)){
        adj.first = Coordinate(pos.x - 1, pos.y + 1);
        adj.second = Coordinate(pos.x + 1, pos.y - 1);
    } else if ((std::abs(angle - M_PI) < DBL_EPSILON) ||
               (std::abs(angle - 0) < DBL_EPSILON) ||
               (std::abs(angle - 2*M_PI) < DBL_EPSILON)) {
        adj.first = Coordinate(pos.x, pos.y - 1);
        adj.second = Coordinate(pos.x, pos.y + 1);
    } else { std::cout << "No hay ninguna posicion alrededor, algo raro paso.\n"; }
    return adj;
}
