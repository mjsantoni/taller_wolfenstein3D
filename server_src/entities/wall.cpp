#include "server/wall.h"

Wall::Wall(std::string id, bool _is_fake) :
            Positionable("wall", id, true),
            is_fake(_is_fake) {
}

Wall::~Wall() {
}

