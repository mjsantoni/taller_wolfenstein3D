#include "server/game/damage_calculator.h"
#include "server/utils/probability.h"

int DamageCalculator::calculateDmg(Player& player, int base_damage,
                                   int pos_travelled, bool is_adjacent) {
    float final_damage = 0;
    double precision = player.getGun().getPrecision();
    int range = player.getGun().getRange();
    Probability prob;
    bool hit = prob(precision);
    if (!hit || pos_travelled > range) { return 0; }

    // Recta que hace que al rango maximo pegue 30% del daño y daño maximo al inicio
    // sea 100% => y = -7/(n/10) * x + 100. Donde N es el rango y X la distancia
    float dmg_multiplier = (float) ((float) -7/((float)range/(float)10) * (float) pos_travelled + (float) 100);

    final_damage = (float) base_damage * dmg_multiplier/100;
    if (is_adjacent) {
        final_damage *= 0.75; // el 0.75 deberia ser una cte de config
    }
    return std::round(final_damage);
}

int DamageCalculator::calculateDamageRPG(Player& player, int base_damage,
                                         Coordinate& explosion_center,
                                         Coordinate& player_position,
                                         int explosion_radius) {
    int distance = explosion_center.distanceTo(player_position);
    std::cout << "El RPG le pega a player " << player.getID() << " a (distancia): " << distance << "\n";
    // Recta que hace que en el lugar mas alejado pegue la mitad del daño y en el centro
    // sea 100% => y = -50/n * x + 100. Donde N es el radio de golpe
    float dmg_multiplier = (float) ((float) -50/explosion_radius * (float) distance + (float) 100);
    float final_damage = (float) base_damage * dmg_multiplier/100;
    std::cout << "Final dmg sin redondeo: " << final_damage << "\n";
    std::cout << "Final dmg con redondeo: " << std::round(final_damage) << "\n";
    return std::round(final_damage);
}
