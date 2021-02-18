#include "server/entities/wall.h"

Wall::Wall(std::string _wall_type, int id) :
            Positionable("wall", _wall_type, id, true),
            is_fake(_is_fake) {
}

Wall::~Wall() {}
