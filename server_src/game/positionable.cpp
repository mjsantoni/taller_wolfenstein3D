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

Positionable::Positionable(const Positionable& other) {
    this->type = other.type;
    this->id = other.id;
    this->is_blocking = other.is_blocking;
}
Positionable& Positionable::operator=(const Positionable& other) {
    this->type = other.type;
    this->id = other.id;
    this->is_blocking = other.is_blocking;
    return *this;
}
