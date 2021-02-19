#ifndef TP_WOLFENSTEIN_DAMAGE_CALCULATOR_H
#define TP_WOLFENSTEIN_DAMAGE_CALCULATOR_H

#include "server/game/player.h"
#include "server/game/coordinate.h"

class DamageCalculator {
public:

    DamageCalculator() {}

    ~DamageCalculator() {}

    int calculateDmg(Player& player, int base_damage,
                     int pos_travelled, bool is_adjacent);

    int calculateDamageRPG(Player &player, int base_damage, Coordinate &explosion_center, Coordinate &player_position,
                           int explosion_radius);
};


#endif //TP_WOLFENSTEIN_DAMAGE_CALCULATOR_H
