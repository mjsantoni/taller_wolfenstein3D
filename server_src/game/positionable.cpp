#include "server/positionable.h"

Positionable::Positionable(std::string _type, bool _is_blocking) :
                           type(_type), is_blocking(_is_blocking) {}

std::string Positionable::getType() {
    return type;
}

bool Positionable::isBlocking() {
    return is_blocking;
}

