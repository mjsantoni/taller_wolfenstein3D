//
// Created by andy on 25/11/20.
//

#include "client/client_positionable.h"

ClientPositionable::ClientPositionable(std::string name, int object_type, bool is_sprite,
                           std::string image_name, std::string unique_name) :
                           object_name(std::move(name)),
                           object_type(object_type),
                           is_sprite(is_sprite),
                           texture_name(std::move(image_name)),
                           unique_name(std::move(unique_name)){
}

std::string ClientPositionable::getObjectName() {
    return object_name;
}

int ClientPositionable::getObjectType() {
    return object_type;
}

bool ClientPositionable::isSprite() {
    return is_sprite;
}

int ClientPositionable::getCurrentImageNumber() {
    return sprite_image_number;
}

std::string ClientPositionable::getTextureName() {
    return texture_name;
}

std::pair<int, int> ClientPositionable::getPosition() {
    return position;
}
