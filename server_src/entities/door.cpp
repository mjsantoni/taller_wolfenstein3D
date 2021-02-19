#include <utility>

#include "server/entities/door.h"

Door::Door(std::string type, int id) :
           Positionable("door", std::move(type), id, true) {}

Door::~Door() {}
