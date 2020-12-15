#include "server/colission_handler.h"
#include <iostream>
#include <cmath>


ColissionHandler::ColissionHandler(Map &_map) : map(_map) {}

std::pair<int, int> ColissionHandler::moveToPosition(std::pair<int, int> actual_pos, double angle) {
    int x_move = std::round(cos(angle)*move_size);
    int y_move = std::round(sin(angle)*move_size*-1);
    int x_factor = (x_move < 0) ? -1 : 1;
    int y_factor = (y_move < 0) ? -1 : 1;
    int i = 0;
    int j = 0;
    bool is_y = abs(x_move) > abs(y_move) ? false : true;
    int for_limit = (is_y) ? abs(y_move) : abs(x_move);
    int for_limit_oposite = (is_y) ? abs(x_move) : abs(y_move);
    int coord_base = (is_y) ? actual_pos.second: actual_pos.first;
    int coord_oposite = (is_y) ? actual_pos.first : actual_pos.second;
    int factor = (is_y) ? y_factor : x_factor;
    int factor_oposite = (is_y) ? x_factor : y_factor;

    for(; i < for_limit; i++) {
        int move_temp = coord_base + factor*safe_distance + factor*i;
        std::pair<int,int> new_position;
        if (is_y) {
            new_position.first = coord_oposite;
            new_position.second = move_temp;
        }
        else {
            new_position.first = move_temp;
            new_position.second = coord_oposite;
        }
        if (map.isABlockingItem(new_position)) continue;
        else {
            i--;
            break;
        }
    }
    for(; j < for_limit_oposite && j < i; j++) {
        int move_temp = coord_oposite + factor_oposite*safe_distance + factor_oposite*j;
        std::pair<int,int> new_position;
        if (is_y) {
            new_position.first = move_temp;
            new_position.second = coord_base;
        }
        else {
            new_position.first = coord_base;
            new_position.second = move_temp;
        }
        if (map.isABlockingItem(new_position)) continue;
        else {
            j--;
            break;
        }
    }
    std::pair<int,int> position;
    if (is_y) {
        position.first = actual_pos.first + j*x_factor;
        position.second = actual_pos.second + i*y_factor;
    } else {
        position.first = actual_pos.first + i*x_factor;
        position.second = actual_pos.second + j*y_factor;
    }
    return position;
}

Positionable
ColissionHandler::getCloseItems(std::pair<int, int> old_pos,
                                std::pair<int, int> new_pos,
                                std::pair<int, int>& pos_positionable) {
    std::pair<int, int> no_item_pos(0,0);
    std::pair<int,int> item_in_pos;
    std::vector<std::pair<int, int>> walked_positions = walkedPositions(old_pos, new_pos);
    for (auto& pos : walked_positions) {
        //std::cout << "Pos walked: (" << pos.first << ", " << pos.second << ")\n";
        item_in_pos = map.closePositionable(2, pos);
        if (item_in_pos != no_item_pos) break;
        //falta preguntar si es un charco de agua q no hace nada (dentro de ese if)
    }
    pos_positionable.first = item_in_pos.first;
    pos_positionable.second = item_in_pos.second;
    return map.getPositionableAt(item_in_pos);
}

std::vector<std::pair<int, int>>
ColissionHandler::walkedPositions(std::pair<int, int> old_pos, std::pair<int, int> new_pos) {
    std::vector<std::pair<int, int>> items;
    int x_old = old_pos.first; int y_old = old_pos.second;
    int x_new = new_pos.first; int y_new = new_pos.second;
    if (x_new == x_old) {
        for (int i = y_old; (y_old < y_new) ? i <= y_new : i >= y_new; (y_old < y_new) ? i++ : i--) {
            std::pair<int, int> pos(x_old,i);
            items.push_back(pos);
        }
    } else if (y_new == y_old) {
        for (int i = x_old; (x_old < x_new) ? i <= x_new : i >= x_new; (x_old < x_new) ? i++ : i--) {
            std::pair<int, int> pos(i,y_old);
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
            std::pair<int, int> pos;
            if (it_on_x) pos = std::make_pair(i, std::round(m * i + b));
            else pos = std::make_pair(std::round(m * i + b), i);
            items.push_back(pos);
        }
    }
    return items;
}

void ColissionHandler::setMap(Map& _map) {
    map = _map;
}

