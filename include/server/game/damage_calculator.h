#ifndef TP_WOLFENSTEIN_DAMAGE_CALCULATOR_H
#define TP_WOLFENSTEIN_DAMAGE_CALCULATOR_H

#include "server/game/player.h"
#include "common/coordinate.h"

class DamageCalculator {
 public:

  DamageCalculator() {}

  ~DamageCalculator() {}

  /* Calcula el daño producido por el arma del player, en funcion de la distancia, el daño base y si esta o no en angulo. */
  int calculateDmg(Player& player, int base_damage,
                   int pos_travelled, bool is_adjacent);

  /* Calcula el daño producido por la explosion de un RPG en funcion de la distancia al centro y el radio de eplosion. */
  int calculateDamageRPG(Player& player, int base_damage, Coordinate& explosion_center, Coordinate& player_position,
                         int explosion_radius);
};

#endif //TP_WOLFENSTEIN_DAMAGE_CALCULATOR_H
