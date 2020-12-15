#include "server/positionable.h"

Positionable::Positionable(std::string _type, std::string _id, bool _is_blocking) :
                           type(_type), id(_id), is_blocking(_is_blocking) {}

std::string Positionable::getType() {
    return type;
}

std::string Positionable::getId() {
    return id;
}

bool Positionable::isBlocking() {
    return is_blocking;
}

