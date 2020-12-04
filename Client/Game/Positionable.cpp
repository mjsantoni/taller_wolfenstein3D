//
// Created by andy on 25/11/20.
//

#include "Positionable.h"

Positionable::Positionable(std::string name, int object_type, bool is_sprite,
                           std::string image_name, std::string unique_name) :
                           object_name(std::move(name)),
                           object_type(object_type),
                           is_sprite(is_sprite),
                           texture_name(std::move(image_name)),
                           unique_name(std::move(unique_name)){
}

std::string Positionable::getObjectName() {
    return object_name;
}

int Positionable::getObjectType() {
    return object_type;
}

bool Positionable::isSprite() {
    return is_sprite;
}

int Positionable::getCurrentImageNumber() {
    return sprite_image_number;
}

std::string Positionable::getTextureName() {
    return texture_name;
}
