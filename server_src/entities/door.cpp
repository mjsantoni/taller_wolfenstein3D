#include "server/entities/door.h"


Door::Door(std::string type, int id, bool _is_locked) :
           Positionable("door", type, id, true),
           is_locked(_is_locked) {
}

bool Door::openDoor() const {
    return !is_locked;
}

bool Door::unlock() {
    is_locked = false;
}


Door::Door(const Door& other) {
    this->is_locked = other.is_locked;
}

Door& Door::operator=(const Door& other) {
    this->is_locked = other.is_locked;
    return *this;
}

Door::~Door() {}
