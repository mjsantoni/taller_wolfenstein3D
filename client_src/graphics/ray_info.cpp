//
// Created by andy on 2/12/20.
//

#include "client/graphics/ray_info.h"

int RayInfo::getObjectType() const {
    return object_type;
}

void RayInfo::setObjectType(int _object_type) {
    object_type = _object_type;
}

double RayInfo::getHitDistance() const {
    return hit_distance;
}

void RayInfo::setHitDistance(double _hit_distance) {
    hit_distance = _hit_distance;
}

double RayInfo::getHitGridPosition() const {
    return hit_grid_position;
}

void RayInfo::setHitGridPosition(double _hit_grid_position) {
    hit_grid_position = _hit_grid_position;
}

std::pair<int, int> RayInfo::getMapStartingPosition() const {
    return map_starting_position;
}

void RayInfo::setMapStartingPosition(
        std::pair<int, int> _map_starting_position) {
    map_starting_position = _map_starting_position;
}
