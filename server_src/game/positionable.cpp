#include "server/positionable.h"

Positionable::Positionable(std::string _type, bool _is_obstructive) :
                           type(_type), is_obstructive(_is_obstructive) {}

std::string Positionable::getType() {
    return type;
}


