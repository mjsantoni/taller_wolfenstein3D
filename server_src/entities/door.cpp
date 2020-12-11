#include "server/door.h"


Door::Door(std::string object_type, bool _is_locked) : 
           Positionable("door", true),
           is_locked(_is_locked) {
}

Door::~Door()
{
}
