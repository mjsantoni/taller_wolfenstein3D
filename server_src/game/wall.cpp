#include "server/wall.h"

Wall::Wall(std::string object_type) : Positionable(object_type, "path", 1, true) {
}

Wall::~Wall() {
}

