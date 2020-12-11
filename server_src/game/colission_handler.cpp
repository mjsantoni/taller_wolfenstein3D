//
// Created by ubuntu on 11/12/20.
//

#include "server/colission_handler.h"
#include <iostream>

ColissionHandler::ColissionHandler(Map &_map) : map(_map) {}

std::pair<int, int> ColissionHandler::moveToPosition(std::pair<int, int> actual_pos, double angle) {
    int x_move = std::round(cos(angle)*move_size);
    int y_move = std::round(sin(angle)*move_size*-1);

    std::pair<int,int> new_position(actual_pos.first + x_move,actual_pos.second + y_move);
    
    if (isValid(new_position))
        return new_position;
    return actual_pos;
}


bool ColissionHandler::isValid(std::pair<int, int> new_position) {
    return true;
}
