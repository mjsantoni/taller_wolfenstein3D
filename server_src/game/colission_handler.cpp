#include "server/colission_handler.h"
#include <iostream>
#include <cmath>


ColissionHandler::ColissionHandler(Map &_map) : map(_map) {}

Coordinate ColissionHandler::moveToPosition(Coordinate actual_pos, double angle) {
    int x_move = std::round(cos(angle)*move_size);
    int y_move = std::round(sin(angle)*move_size*-1);
    int x_factor = (x_move < 0) ? -1 : 1;
    int y_factor = (y_move < 0) ? -1 : 1;
    int i = 0;
    int j = 0;
    bool is_y = abs(x_move) > abs(y_move) ? false : true;
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
        if (map.isABlockingItem(new_position)) continue;
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
        if (map.isABlockingItem(new_position)) continue;
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

Positionable
ColissionHandler::getCloseItems(Coordinate old_pos,
                                Coordinate new_pos,
                                Coordinate& pos_positionable) {
    Coordinate no_item_pos(0,0);
    Coordinate item_in_pos(-1, -1);
    std::vector<Coordinate> walked_positions = walkedPositions(old_pos, new_pos);
    for (auto& pos : walked_positions) {
        std::cout << "Pos walked: (" << pos.x << ", " << pos.y << ")\n";
        Coordinate item_pos_aux = map.closePositionable(2, pos);
        item_in_pos.x = item_pos_aux.x;
        item_in_pos.y = item_pos_aux.y;
        if (item_in_pos != no_item_pos) break;
        //falta preguntar si es un charco de agua q no hace nada (dentro de ese if)
    }
    pos_positionable.x = item_in_pos.x;
    pos_positionable.y = item_in_pos.y;
    return map.getPositionableAt(item_in_pos);
}

std::vector<Coordinate>
ColissionHandler::walkedPositions(Coordinate old_pos, Coordinate new_pos) {
    std::vector<Coordinate> items;
    std::cout << "walked\n";
    std::cout << "Old: x: " << old_pos.x << " - y: " << old_pos.y << "\n";
    std::cout << "New: x: " << new_pos.x << " - y: " << new_pos.y << "\n";
    int x_old = old_pos.x; int y_old = old_pos.y;
    int x_new = new_pos.x; int y_new = new_pos.y;
    if (x_new == x_old) {
        for (int i = y_old; (y_old < y_new) ? i <= y_new : i >= y_new; (y_old < y_new) ? i++ : i--) {
            Coordinate pos(x_old,i);
            items.push_back(pos);
        }
    } else if (y_new == y_old) {
        for (int i = x_old; (x_old < x_new) ? i <= x_new : i >= x_new; (x_old < x_new) ? i++ : i--) {
            Coordinate pos(i,y_old);
            items.push_back(pos);
        }
    } else {
        bool it_on_x = abs(y_new - y_old) < abs(x_new - x_old);
        double m = (it_on_x) ? ((double) (y_new - y_old) / (x_new - x_old)) :
                               ((double) (x_new - x_old) / (y_new - y_old));
        double b = (double) y_old - (m * x_old);
        int axis_old = it_on_x ? x_old : y_old;
        int axis_new = it_on_x ? x_new : y_new;
        //Si se quiere algo mucho mas aproximado no hacer el for del else
        //y solo hacer el primer for. Esto es mucho mas overfiteado.
        for (int i = axis_old; (axis_old < axis_new) ? i <= axis_new : i >= axis_new; (axis_old < axis_new) ? i++ : i--) {
            Coordinate pos(-1, -1);
            if (it_on_x) {
                //std::cout << "AntesITX: " << pos.x << " - Y: " << pos.y << "\n";
                pos.x = i;
                pos.y = std::round(m * i + b);
                //std::cout << "DespsITX: " << pos.x << " - Y: " << pos.y << "\n";
                //pos = std::make_pair(i, std::round(m * i + b));
            }
            else {
                //std::cout << "AntesX: " << pos.x << " - Y: " << pos.y << "\n";
                pos.x = std::round(m * i + b); // esto esta roto
                pos.y = i;
                //std::cout << "DespsX: " << pos.x << " - Y: " << pos.y << "\n";
                //pos = std::make_pair(std::round(m * i + b), i);
            }
            items.push_back(pos);
        }
    }
    return items;
}

void ColissionHandler::setMap(Map& _map) {
    map = _map;
}

