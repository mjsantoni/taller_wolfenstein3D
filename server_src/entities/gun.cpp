#include "server/entities/gun.h"

Gun::Gun(std::string type, int id, int _bullets_per_spray,
         double _fire_rate, double _precision) :
         Positionable("gun", type, id, false),
         bullets_per_spray(_bullets_per_spray),
         fire_rate(_fire_rate), 
         precision(_precision) {
}

int Gun::getDamage() {return damage;} // falta calcular bien el resto

Gun::~Gun() {}

int Gun::getRange() {return 15;}
