#include "server/shoot_handler.h"
#include "server/coordinate.h"
#include "server/player.h"
#include <vector>
#include <tgmath.h>
#include "server/positions_calculator.h"

void ShootHandler::algo(Player& player, double angle){
    int range = 15; //player.getEquippedWeapon().getRange();
    int x_move = std::round(cos(angle)*range);
    int y_move = std::round(sin(angle)*range*-1);
    Coordinate player_pos = map.getPlayerPosition(0);
    Coordinate new_pos(player_pos.x + x_move, player_pos.y + y_move);
    PositionsCalculator ph;
    std::vector<Coordinate> straight_line = ph.straightLine(player_pos, new_pos);
    for (auto& pos : straight_line) {
        if (!map.isABlockingItem(pos)) break;
        if (map.isAPlayerAt(pos)) {
            std::cout << "PlayerFound\n";
            break;
            //Player enemy = map.getPlayerAt(pos);
            //shootEnemy(player,enemy);
        }
    }
}