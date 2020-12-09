#include "server/bullets.h"


Bullets::Bullets() : Positionable("Bullets", "path", 1, false),
                     bullets_given(5) {
}

Bullets::~Bullets()
{
}