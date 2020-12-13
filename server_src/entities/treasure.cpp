#include "server/treasure.h"


Treasure::Treasure(int _points_given, std::string object_type) : 
                   Positionable(object_type, false),
                   points_given(_points_given) {
}

Treasure::~Treasure()
{
}