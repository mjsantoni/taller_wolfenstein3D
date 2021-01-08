#include "server/entities/door.h"


Door::Door(std::string id, bool _is_locked) :
           Positionable("door", "door", id, true),
           is_locked(_is_locked) {
}

Door::~Door()
{
}
