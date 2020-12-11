//
// Created by ubuntu on 11/12/20.
//

#include "server/colission_handler.h"
#include <iostream>

ColissionHandler::ColissionHandler(Map &_map) : map(_map) {}

std::pair<int, int> ColissionHandler::moveToPosition(std::pair<int, int> actual_pos, double angle) {
    int x_move = std::round(cos(angle)*move_size);
    int y_move = std::round(sin(angle)*move_size*-1);

    std::cout << "NEW X: " <<  x_move << "\n";
    std::cout << "NEW Y: " <<  y_move << "\n";

    int x_factor = (x_move < 0) ? -1 : 1;
    int y_factor = (y_move < 0) ? -1 : 1;

    int i = 0;
    int j = 0;

    for(; j < abs(y_move); j++) {
        int y_move_temp = actual_pos.second + y_factor*safe_distance + y_factor*j;
        std::pair<int,int> new_position(actual_pos.first, y_move_temp);
        if (map.isABlockingItem(new_position)) {
            continue;
        } else {
            j--;
            break; }
    }

    for(; i < j; i++) {
        int x_move_temp = actual_pos.first + x_factor*safe_distance + x_factor*i;
        std::pair<int,int> new_position(x_move_temp,actual_pos.second);
        if (map.isABlockingItem(new_position)) {
            continue;
        } else {
            i--;
            break; }
    }

    std::pair<int,int> position(actual_pos.first + i*x_factor,actual_pos.second + j*y_factor);
    return position;
}

bool ColissionHandler::isValid(std::pair<int, int> new_position) {
    return map.isABlockingItem(new_position);
}
