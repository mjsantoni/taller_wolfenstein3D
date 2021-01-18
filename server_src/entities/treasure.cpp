#include "server/entities/treasure.h"

Treasure::Treasure(std::string type, int id, int _points_given) :
                    Positionable("treasure", type, id, false),
                    points_given(_points_given) {}


int Treasure::getPoints() {
    return points_given;
}

Treasure::Treasure(const Treasure& other) {
    this->category = other.category;
    this->type = other.type;
    this->id = other.id;
    this->is_blocking = other.is_blocking;
    this->points_given = other.points_given;
}

Treasure& Treasure::operator=(const Treasure& other) {
    this->category = other.category;
    this->type = other.type;
    this->id = other.id;
    this->is_blocking = other.is_blocking;
    this->points_given = other.points_given;
    return *this;
}

Treasure::~Treasure() {}