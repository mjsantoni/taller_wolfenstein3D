#include "server/game/colission_handler.h"
#include <iostream>
#include <cmath>
#include "server/game/positions_calculator.h"
#include <set>

ColissionHandler::ColissionHandler(Map &_map) : map(_map) {}

Coordinate ColissionHandler::moveToPosition(const Coordinate& actual_pos, double angle) {
    int x_move = std::round(cos(angle)*move_size);
    int y_move = std::round(sin(angle)*move_size*-1);
    int x_factor = (x_move < 0) ? -1 : 1;
    int y_factor = (y_move < 0) ? -1 : 1;
    int i = 0; int j = 0;
    bool is_y = abs(x_move) <= abs(y_move); // abs(x_move) > abs(y_move) ? false : true;
    int for_limit = (is_y) ? abs(y_move) : abs(x_move);
    int for_limit_oposite = (is_y) ? abs(x_move) : abs(y_move);
    int coord_base = (is_y) ? actual_pos.y: actual_pos.x;
    int coord_oposite = (is_y) ? actual_pos.x : actual_pos.y;
    int factor = (is_y) ? y_factor : x_factor;
    int factor_oposite = (is_y) ? x_factor : y_factor;

    for(; i < for_limit; i++) {
        int move_temp = coord_base + factor*safe_distance + factor*i;
        Coordinate new_position(-1, -1);
        if (is_y) {
            new_position.x = coord_oposite;
            new_position.y = move_temp;
        }
        else {
            new_position.x = move_temp;
            new_position.y = coord_oposite;
        }
        if (!map.isABlockingItemAt(new_position)) continue;
        else {
            i--;
            break;
        }
    }
    for(; j < for_limit_oposite && j < i; j++) {
        int move_temp = coord_oposite + factor_oposite*safe_distance + factor_oposite*j;
        Coordinate new_position(-1, -1);
        if (is_y) {
            new_position.x = move_temp;
            new_position.y = coord_base;
        }
        else {
            new_position.x = coord_base;
            new_position.y = move_temp;
        }
        if (!map.isABlockingItemAt(new_position)) continue;
        else {
            j--;
            break;
        }
    }
    Coordinate position(-1, -1);
    if (is_y) {
        position.x = actual_pos.x + j*x_factor;
        position.y = actual_pos.y + i*y_factor;
    } else {
        position.x = actual_pos.x + i*x_factor;
        position.y = actual_pos.y + j*y_factor;
    }
    return position;
}

std::vector<std::pair<Coordinate, Positionable>>
ColissionHandler::getCloseItems(const Coordinate& old_pos,
                                const Coordinate& new_pos) {
    std::vector<std::pair<Coordinate, Positionable>> positionables;
    std::set<Coordinate> found_positionables;
    Coordinate no_item_pos(0,0); Coordinate item_in_pos(-1, -1);
    PositionsCalculator ph;
    std::vector<Coordinate> walked_positions = ph.straightLine(old_pos, new_pos);
    for (auto& pos : walked_positions) {
        //std::cout << "Pos walked: (" << pos.x << ", " << pos.y << ")\n";
        Coordinate item_pos_aux = map.closePositionable(2, pos, found_positionables);
        item_in_pos.x = item_pos_aux.x;
        item_in_pos.y = item_pos_aux.y;
        if (item_in_pos != no_item_pos &&
            map.getPositionableAt(item_in_pos).getType() != "water_puddle") {
            //std::cout << "Pickupeo un: " << map.getPositionableAt(item_in_pos).getType() << "\n";
            std::pair<Coordinate, Positionable>
                    item_to_pickup(item_in_pos, map.getPositionableAt(item_in_pos));
            positionables.push_back(item_to_pickup);
        }
    }
    return positionables;
}

/* Verifica en linea recta hacia donde mira el jugador una cantidad
 * move size + safe distance de distancia total si existe una pared
 */
Coordinate ColissionHandler::getCloseBlocking(Coordinate pos, double angle, std::string category) {
    int x_move = std::round(cos(angle)*move_size);
    int y_move = std::round(sin(angle)*move_size*-1);
    int x_factor = (x_move < 0) ? -1 : 1;
    int y_factor = (y_move < 0) ? -1 : 1;
    int new_x = pos.x + x_move + (safe_distance * x_factor);
    int new_y = pos.y + y_move + (safe_distance * y_factor);
    Coordinate pos_to_check(new_x, new_y);
    if (map.isABlockingItemAt(pos_to_check)) {
        if (map.getBlockingItemAt(pos_to_check).getCategory() == category) {
            std::cout << "Hay un: " << map.getBlockingItemAt(pos_to_check).getCategory() << "\n";
            return pos_to_check;
        }
    }
    return Coordinate(-1, -1);
}
