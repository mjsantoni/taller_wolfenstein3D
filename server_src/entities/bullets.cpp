#include "server/entities/bullets.h"

Bullets::Bullets(std::string id, int _bullets_given) :
                 Positionable("bullets", "bullets", id, false),
                 bullets_given(_bullets_given) {
}

Bullets::~Bullets()
{
}