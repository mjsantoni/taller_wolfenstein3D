#include "server/door.h"


Door::Door(std::string object_type, bool _is_locked) : 
           Positionable(object_type, "path", 1, true),
           is_locked(_is_locked) {
}

Door::~Door()
{
}
