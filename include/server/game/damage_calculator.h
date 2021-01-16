#ifndef TP_WOLFENSTEIN_DAMAGE_CALCULATOR_H
#define TP_WOLFENSTEIN_DAMAGE_CALCULATOR_H

#include "player.h"
#include "coordinate.h"

class DamageCalculator {
public:

    DamageCalculator() {}

    ~DamageCalculator() {}

    int calculate_dmg(Player& player, int base_damage,
                      int pos_travelled, bool is_adjacent);
};


#endif //TP_WOLFENSTEIN_DAMAGE_CALCULATOR_H
