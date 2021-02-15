#ifndef TP_WOLFENSTEIN_SHOOT_HANDLER_H
#define TP_WOLFENSTEIN_SHOOT_HANDLER_H

#include "map.h"
#include "hit.h"
#include "server/entities/rpg.h"
#include "server/game/damage_calculator.h"
#include "common/change.h"
#include "server/game/score_handler.h"


class ShootHandler {
private:
    Map& map;
    std::map<int, RPG> rpgs;
    DamageCalculator dmg_calculator;
    ScoreHandler& scoreHandler;


public:
    ShootHandler(Map& _map, ScoreHandler& _sh) : map(_map), scoreHandler(_sh) {}

    std::pair<Hit, std::vector<Change>> shoot(Player& player, double angle, std::vector<Player>& players);

    int hit(Player &player, Player &enemy, int damage, bool &enemy_dies);

    std::vector<Coordinate> getAdjacents(Coordinate &pos, double angle, int adj_units_to_check);

    bool hitAtPos(std::vector<Coordinate>& positions, std::vector<Player>& players, Player& player,
                  std::vector<std::pair<int, int>>& enemy_dmg_done, int pos_travelled,
                  bool is_adjacent);

    std::vector<int> playersInArea(Coordinate &coord, int units);


    Hit shootRegularGun(int bullets_to_shoot, Player &player, std::vector<Coordinate> &straight_line,
                        std::vector<std::pair<int, int>> &enemy_dmg_done, std::vector<Player> &players);

    void
    hitPlayersWithRPG(std::vector<int> &players_found, Player &player, Coordinate explosion_center,
                      std::vector<std::pair<int, int>> &enemy_dmg_done, std::vector<Player> &players);

    Hit shootRPG(int bullets_to_shoot, Player &player, std::vector<Coordinate> straight_line,
                 std::vector<std::pair<int, int>> &enemy_dmg_done, std::vector<Player> &players,
                 std::vector<Change> &changes);

    Hit travelAndExplodeRPG(RPG &rpg, int bullets_to_shoot, std::vector<std::pair<int, int>> &enemy_dmg_done,
                            std::vector<Player> &players);

    Hit travelAndExplodeAllRPGS(std::vector<Player> &players, std::vector<Change> &changes);
};


#endif //TP_WOLFENSTEIN_SHOOT_HANDLER_H
