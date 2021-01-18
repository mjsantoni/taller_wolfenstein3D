#include "server/entities/wall.h"

Wall::Wall(std::string type, int id, bool _is_fake) :
            Positionable("wall", type, id, true),
            is_fake(_is_fake) {
}

Wall::Wall(const Wall& other) {
    this->is_fake = other.is_fake;
}

Wall& Wall::operator=(const Wall& other) {
    this->is_fake = other.is_fake;
    return *this;
}

Wall::~Wall() {
}

