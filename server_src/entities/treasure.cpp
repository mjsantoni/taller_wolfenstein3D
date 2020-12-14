#include "server/treasure.h"

Treasure::Treasure(int _points_given, std::string id) :
                   Positionable("treasure", id, false),
                   points_given(_points_given) {
}

int Treasure::getPoints() {
    return points_given;
}

Treasure::~Treasure()
{
}