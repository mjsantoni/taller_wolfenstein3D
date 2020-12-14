#include "server/gun.h"

Gun::Gun(int _bullets_per_spray, double _fire_rate, 
         double _precision, std::string id) :
         Positionable("gun", id, false),
         bullets_per_spray(_bullets_per_spray),
         fire_rate(_fire_rate), 
         precision(_precision) {
}

Gun::~Gun() {
}
