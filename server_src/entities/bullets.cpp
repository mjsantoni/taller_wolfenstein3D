#include "server/bullets.h"


Bullets::Bullets(std::string id) : Positionable("bullets", id, false),
                     bullets_given(5) {
}

Bullets::~Bullets()
{
}