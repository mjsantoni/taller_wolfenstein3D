#include "server/entities/gun.h"

Gun::Gun(std::string type, std::string id, int _bullets_per_spray,
         double _fire_rate, double _precision) :
         Positionable("gun", type, id, false),
         bullets_per_spray(_bullets_per_spray),
         fire_rate(_fire_rate), 
         precision(_precision) {
}

Gun::~Gun() {}
