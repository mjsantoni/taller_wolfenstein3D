//
// Created by andy on 11/12/20.
//

#include "client/positionable_mock.h"

PositionableMock::PositionableMock(std::string name, int object_type, bool is_sprite,
                                   std::string image_name, std::string unique_name,
                                   int object_width, int object_height) :
        object_name(std::move(name)),
        object_type(object_type),
        is_sprite(is_sprite),
        texture_name(std::move(image_name)),
        unique_name(std::move(unique_name)),
        object_width(object_width),
        object_height(object_height) {
}

PositionableMock::PositionableMock(std::string name, int object_type, bool is_sprite,
                                   std::string image_name, int object_width,
                                   int object_height) :
        object_name(std::move(name)),
        object_type(object_type),
        is_sprite(is_sprite),
        texture_name(std::move(image_name)),
        object_width(object_width),
        object_height(object_height) {
}


std::string PositionableMock::getObjectName() {
    return object_name;
}

int PositionableMock::getObjectType() {
    return object_type;
}

bool PositionableMock::isSprite() {
    return is_sprite;
}

int PositionableMock::getCurrentImageNumber() {
    return sprite_image_number;
}

std::string PositionableMock::getTextureName() {
    return texture_name;
}

void PositionableMock::setPosition(int x_pos, int y_pos) {
    position = std::pair<int, int>{x_pos, y_pos};
}

std::pair<int, int> PositionableMock::getPosition() {
    return position;
}

int PositionableMock::getWidth() {
    return object_width;
}

int PositionableMock::getHeight() {
    return object_height;
}

