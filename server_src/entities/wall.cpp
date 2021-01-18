#include "server/entities/wall.h"

Wall::Wall(std::string type, int id, bool _is_fake) :
            Positionable("wall", type, id, true),
            is_fake(_is_fake) {
}

Wall::Wall(const Wall& other) {
    this->category = other.category;
    this->type = other.type;
    this->id = other.id;
    this->is_blocking = other.is_blocking;
    this->is_fake = other.is_fake;
}

Wall& Wall::operator=(const Wall& other) {
    this->category = other.category;
    this->type = other.type;
    this->id = other.id;
    this->is_blocking = other.is_blocking;
    this->is_fake = other.is_fake;
    return *this;
}

Wall::~Wall() {
}

