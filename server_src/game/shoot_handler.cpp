#include "server/shoot_handler.h"
#include "server/coordinate.h"
#include "server/player.h"
#include <vector>
#include <tgmath.h>
#include "server/positions_calculator.h"

void ShootHandler::shoot(Player& player, double angle, std::vector<Player> players){
    int range = 15; //player.getEquippedWeapon().getRange();
    int x_move = std::round(cos(angle)*range);
    int y_move = std::round(sin(angle)*range*-1);
    Coordinate player_pos = map.getPlayerPosition(0);
    Coordinate new_pos(player_pos.x + x_move, player_pos.y + y_move);
    PositionsCalculator ph;
    std::vector<Coordinate> straight_line = ph.straightLine(player_pos, new_pos);
    straight_line = std::vector<Coordinate>(straight_line.begin() + 1, straight_line.end());

    for (auto& pos : straight_line) {
        if (!map.isABlockingItem(pos)) break;
        if (map.isAPlayerAt(pos)) {
            int id = map.getPlayerIDAtPosition(pos);
            Player enemy = players[id];
            hit(player,enemy,15);
        }
    }
}

void ShootHandler::hit(Player& player, Player& enemy, int damage) {
    player.reduceAmmo();
    enemy.reduceHP(damage);
}