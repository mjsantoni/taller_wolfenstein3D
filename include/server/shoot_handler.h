#ifndef TP_WOLFENSTEIN_SHOOT_HANDLER_H
#define TP_WOLFENSTEIN_SHOOT_HANDLER_H

#include "server/map.h"

class ShootHandler {
private:
    Map& map;
public:
    ShootHandler(Map& _map) : map(_map) {}

    void algo(Player &player, double angle);
};


#endif //TP_WOLFENSTEIN_SHOOT_HANDLER_H
