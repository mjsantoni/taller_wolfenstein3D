#include "server/entities/door.h"


Door::Door(std::string type, int id, bool _is_locked) :
           Positionable("door", type, id, true),
           is_locked(_is_locked) {
}

Door::~Door()
{
}
