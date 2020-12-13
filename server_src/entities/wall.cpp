#include "server/wall.h"

Wall::Wall(std::string _wall_type, bool _is_fake) :
            Positionable(_wall_type, true), wall_type(_wall_type),
            is_fake(_is_fake) {
}

Wall::~Wall() {
}

