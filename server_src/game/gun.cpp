#include "server/gun.h"

Gun::Gun(int _bullets_per_spray, double _fire_rate, 
         double _precision, std::string object_type) :
         Positionable(object_type, "path", 1, false),
         bullets_per_spray(_bullets_per_spray),
         fire_rate(_fire_rate), 
         precision(_precision) {
}

Gun::~Gun() {
}
