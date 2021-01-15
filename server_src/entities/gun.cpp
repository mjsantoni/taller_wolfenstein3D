#include "server/entities/gun.h"
#include <iostream>
#include <random>

Gun::Gun(std::string type, int id, int _bullets_per_spray,
         double _fire_rate, double _precision) :
         Positionable("gun", type, id, false),
         bullets_per_spray(_bullets_per_spray),
         fire_rate(_fire_rate), 
         precision(_precision) {
}

int Gun::getDamage() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist10(1,10); // distribution in range [1, 10]
    //return dist10(rng);
    return 10; //dejo esto por ahora para test
} // falta calcular bien el resto

double Gun::getPrecision() { return precision; }

int Gun::getBulletsPerSpray() { return bullets_per_spray; }

Gun::~Gun() {}

int Gun::getRange() {return 15;}



Gun::Gun(const Gun& other) {
    this->bullets_per_spray = other.bullets_per_spray;
    this->fire_rate = other.fire_rate;
    this->precision = other.precision;
    this->category = other.category;
    this->type = other.type;
    this->id = other.id;
    this->is_blocking = other.is_blocking;
}
Gun& Gun::operator=(const Gun& other) {
    this->bullets_per_spray = other.bullets_per_spray;
    this->fire_rate = other.fire_rate;
    this->precision = other.precision;
    this->category = other.category;
    this->type = other.type;
    this->id = other.id;
    this->is_blocking = other.is_blocking;
    return *this;
}



