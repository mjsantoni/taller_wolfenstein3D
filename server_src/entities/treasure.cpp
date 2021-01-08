#include "server/entities/treasure.h"

Treasure::Treasure(std::string type, std::string id, int _points_given) :
                    Positionable("treasure", type, id, false),
                    points_given(_points_given) {}


int Treasure::getPoints() {
    return points_given;
}

Treasure::~Treasure() {}