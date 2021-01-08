#ifndef TP_WOLFENSTEIN_SHOOT_HANDLER_H
#define TP_WOLFENSTEIN_SHOOT_HANDLER_H

#include "map.h"

class ShootHandler {
private:
    Map& map;
public:
    ShootHandler(Map& _map) : map(_map) {}

    void shoot(Player& player, double angle, std::vector<Player> players);

    void hit(Player &player, Player &enemy, int damage);
};


#endif //TP_WOLFENSTEIN_SHOOT_HANDLER_H
