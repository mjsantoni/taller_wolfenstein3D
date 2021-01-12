#include "server/game/shoot_handler.h"
#include "server/game/coordinate.h"
#include "server/game/player.h"
#include <vector>
#include <tgmath.h>
#include "server/game/positions_calculator.h"

void ShootHandler::shoot(Player& player, double angle, std::vector<Player>& players){
    //return std::vector<std::pair<int,int>>
    // el primero es el id del hiteado y el segundo el daño recibido.
    // si alguno se muere pongo que recibio daño -1.
    int damage = player.getGun().getDamage();
    int range = player.getGun().getRange();
    int x_move = std::round(cos(angle)*range);
    int y_move = std::round(sin(angle)*range*-1);
    Coordinate player_pos = map.getPlayerPosition(0);
    Coordinate new_pos(player_pos.x + x_move, player_pos.y + y_move);
    PositionsCalculator ph;
    std::vector<Coordinate> straight_line = ph.straightLine(player_pos, new_pos);
    straight_line = std::vector<Coordinate>(straight_line.begin() + 1, straight_line.end());

    for (auto& pos : straight_line) {
        if (map.isABlockingItemAt(pos)) break;
        if (map.isAPlayerAt(pos)) {
            int id = map.getPlayerIDAtPosition(pos);
            Player& enemy = players[id];
            hit(player,enemy, damage);
        }
    }
}
//hit deberia ser parte del game, que se encargue de restar vidas y eso,
// el shoot handler solo devuelve player q recibe daño y el daño
void ShootHandler::hit(Player& player, Player& enemy, int damage) {
    player.reduceAmmo();
    enemy.reduceHP(damage);
}