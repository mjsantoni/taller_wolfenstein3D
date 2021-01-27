#ifndef TP_WOLFENSTEIN_SHOOT_HANDLER_H
#define TP_WOLFENSTEIN_SHOOT_HANDLER_H

#include "map.h"
#include "hit.h"
#include "server/entities/rpg.h"

class ShootHandler {
private:
    Map& map;
    std::vector<RPG> rpgs;

public:
    ShootHandler(Map& _map) : map(_map) {}

    Hit shoot(Player& player, double angle, std::vector<Player>& players);

    int hit(Player &player, Player &enemy, int damage, bool &enemy_dies, int bullets_used);

    std::pair<Coordinate, Coordinate> getAdjacents(Coordinate &pos, double angle);

    bool hitAtPos(Coordinate& pos, std::vector<Player>& players, Player& player,
                  std::vector<std::pair<int, int>>& enemy_dmg_done, int pos_travelled,
                  bool is_adjacent);

    std::vector<int> playersInArea(Coordinate &coord, int units);
};


#endif //TP_WOLFENSTEIN_SHOOT_HANDLER_H
