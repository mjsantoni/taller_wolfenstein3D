#include "server/entities/wall.h"

Wall::Wall(std::string type, bool _is_fake) :
            Positionable("wall", type, "id", true),
            is_fake(_is_fake) {
}

Wall::~Wall() {
}

