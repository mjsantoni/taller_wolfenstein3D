#include <utility>

#include "server/entities/wall.h"

Wall::Wall(std::string _wall_type, int id) :
            Positionable("wall", std::move(_wall_type), id, true) {}

Wall::~Wall() {}
