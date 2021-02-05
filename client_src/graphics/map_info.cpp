//
// Created by andy on 1/12/20.
//

#include "client/map_info.h"

double MapInfo::getObjectWidth() const {
    return object_width;
}

void MapInfo::setObjectWidth(double _object_width) {
    object_width = _object_width;
}

double MapInfo::getObjectHeight() const {
    return object_height;
}

void MapInfo::setObjectHeight(double _object_height) {
    object_height = _object_height;
}

int MapInfo::getObjectSide() const {
    return object_side;
}

void MapInfo::setObjectSide(int _object_side) {
    object_side = _object_side;
}

double MapInfo::getHitDistance() const {
    return hit_distance;
}

void MapInfo::setHitDistance(double _hit_distance) {
    hit_distance = _hit_distance;
}

double MapInfo::getHitGridPos() const {
    return hit_grid_pos;
}

void MapInfo::setHitGridPos(double _hit_grid_pos) {
    hit_grid_pos = _hit_grid_pos;
}

std::pair<int, int> MapInfo::getMapStartingPos() const {
    return map_starting_pos;
}

void MapInfo::setMapStartingPos(std::pair<int, int> _map_starting_pos) {
    map_starting_pos = _map_starting_pos;
}
