//
// Created by andy on 10/12/20.
//

#include "client/drawable.h"

Drawable::Drawable(int _object_type) : object_type(_object_type),
                                       sprite_animation_no(0) {}

Drawable::Drawable(int _object_type, int _sprite_animation_no) :
         object_type(_object_type), sprite_animation_no(_sprite_animation_no) {}

int Drawable::getObjectType() {
    return object_type;
}

std::pair<int, int> Drawable::getMapPosition() {
    return map_position;
}

int Drawable::getMapWidth() {
    return map_width;
}

std::string Drawable::getObjectName() {
    return object_name;
}

void Drawable::setMapWidth(int width) {
    map_width = width;
}

void Drawable::setMapPosition(int x_pos, int y_pos) {
    std::pair<int, int> new_position{x_pos, y_pos};
    map_position = new_position;
}

void Drawable::setObjectName(std::string name) {
    object_name = name;
}

int Drawable::getId() const {
    return id;
}

void Drawable::setId(int _id) {
    id = _id;
}
