//
// Created by ubuntu on 11/12/20.
//

#ifndef TP_WOLFENSTEIN_COLISSION_HANDLER_H
#define TP_WOLFENSTEIN_COLISSION_HANDLER_H

#include "server/map.h"

class ColissionHandler {
private:
    Map& map;
    int move_size = 10;
    int safe_distance = 10;
public:
    ColissionHandler(Map& _map);
    std::pair<int,int> moveToPosition(std::pair<int,int> actual_pos, double angle);
    bool isValid(std::pair<int,int> new_position);
};


#endif //TP_WOLFENSTEIN_COLISSION_HANDLER_H
