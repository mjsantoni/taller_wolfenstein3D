#include "server/entities/water_puddle.h"

WaterPuddle::WaterPuddle(int id) :
        Positionable("water_puddle", "water_puddle", id, false) {
}

WaterPuddle::~WaterPuddle()
{
}
