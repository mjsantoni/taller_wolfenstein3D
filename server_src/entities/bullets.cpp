#include "server/entities/bullets.h"

Bullets::Bullets(int id, int _bullets_given, std::string type) :
                 Positionable("bullets", type, id, false),
                 bullets_given(_bullets_given) {}

Bullets::~Bullets() {}
