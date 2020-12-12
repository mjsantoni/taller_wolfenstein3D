//
// Created by ubuntu on 11/12/20.
//

#include "server/colission_handler.h"
#include <iostream>

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
        //std::cout << "NEW_X: " << new_position.first << " - NEW_Y: " << new_position.second << "\n";

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
    //std::cout << "I: " << i << "\n";
    //std::cout << "J: " << j << "\n";
    std::pair<int,int> position;
    if (is_y) {
        position.first = actual_pos.first + j*x_factor;
        position.second = actual_pos.second + i*y_factor;
    } else {
        position.first = actual_pos.first + i*x_factor;
        position.second = actual_pos.second + j*y_factor;
    }
    //std::pair<int,int> position(actual_pos.first + i*x_factor,actual_pos.second + j*y_factor);
    return position;
}
