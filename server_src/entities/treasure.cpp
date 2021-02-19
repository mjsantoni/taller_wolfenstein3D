#include <utility>

#include "server/entities/treasure.h"

Treasure::Treasure(std::string type, int id, int _points_given) :
                    Positionable("treasure", std::move(type), id, false),
                    points_given(_points_given) {}


int Treasure::getPoints() { return points_given; }

Treasure::~Treasure() {}
