#include "server/game/damage_calculator.h"
#include "server/game/probability.h"

int DamageCalculator::calculateDmg(Player& player, int base_damage,
                                   int pos_travelled, bool is_adjacent) {
    float final_damage = 0;
    double precision = player.getGun().getPrecision();
    Probability prob;
    bool hit = prob(precision);
    std::cout << "Arma con precision: " << precision << "\n";
    if (!hit || pos_travelled > player.getGun().getRange()) {
        std::cout << "No va a pegarle\n";
        return 0;
    }
    std::cout << "Va a pegarle, pos traveled: " << pos_travelled << "\n";

    // Multiplcador con recta y = -10/11 x + 1110/11 para obtener 100% daño
    // a 1 unidad y 10% daño a 100 unidades.
    float dmg_multiplier = (float) ((float) -10/11 *
                           (float) pos_travelled + (float) 1110/11);
    std::cout << "Dmg multip: " << dmg_multiplier/100 << "\n";

    final_damage = (float) base_damage * dmg_multiplier/100;
    if (is_adjacent) {
        final_damage *= 0.75; // el 0.75 deberia ser una cte de config
        std::cout << "final dmg sin redondeo ADJ: " << (final_damage * 0.75) << "\n";
    }
    std::cout << "base dmg sin redondeo: " << base_damage << "\n";
    std::cout << "Final dmg sin redondeo: " << final_damage << "\n";
    std::cout << "Final dmg con redondeo: " << std::round(final_damage) << "\n";
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
