#include "server/entities/gun.h"
#include <iostream>
#include <random>

Gun::Gun() : Positionable("gun", "null", -1, false) {}

Gun::Gun(std::string type, int id, int _bullets_per_spray,
         double _fire_rate, double _precision, int _range) :
         Positionable("gun", type, id, false),
         bullets_per_spray(_bullets_per_spray),
         fire_rate(_fire_rate), 
         precision(_precision),
         range(_range) {
}

int Gun::getDamage() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist10(1,10);
    return dist10(rng);
}

double Gun::getPrecision() { return precision; }

int Gun::getBulletsPerSpray() { return bullets_per_spray; }

Gun::~Gun() {}

int Gun::getRange() { return range; } //rango viene por config



Gun::Gun(const Gun& other) {
    this->bullets_per_spray = other.bullets_per_spray;
    this->fire_rate = other.fire_rate;
    this->precision = other.precision;
    this->category = other.category;
    this->type = other.type;
    this->id = other.id;
    this->is_blocking = other.is_blocking;
    this->range = other.range;
}
Gun& Gun::operator=(const Gun& other) {
    this->bullets_per_spray = other.bullets_per_spray;
    this->fire_rate = other.fire_rate;
    this->precision = other.precision;
    this->category = other.category;
    this->type = other.type;
    this->id = other.id;
    this->is_blocking = other.is_blocking;
    this->range = other.range;
    return *this;
}



