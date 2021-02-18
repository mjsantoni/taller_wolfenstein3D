#include "server/entities/door.h"

Door::Door(std::string type, int id) :
           Positionable("door", type, id, true) {}

Door::~Door() {}
