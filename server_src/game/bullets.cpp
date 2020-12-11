#include "server/bullets.h"


Bullets::Bullets() : Positionable("bullets", false),
                     bullets_given(5) {
}

Bullets::~Bullets()
{
}