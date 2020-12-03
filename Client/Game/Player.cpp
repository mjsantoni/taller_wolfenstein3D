//
// Created by andy on 25/11/20.
//

#include <functional>
#include "Player.h"

Player::Player(std::string name, std::string image_path, int rows, int cols) :
            Positionable("Player"), name(std::move(name)),
            image(std::move(image_path), rows, cols) {
}

std::string Player::getPlayerName() {
    return std::ref(name);
}

SDL_Texture* Player::getImage(SDL_Renderer* renderer, Area& src_area) {
    return image.loadNextTexture(renderer, src_area);
}

double Player::getDirection() {
    return direction;
}

void Player::updateDirection(double offset) {
    double new_direction = direction + offset;
    if (new_direction >= 2*M_PI)
        new_direction -= 2*M_PI;
    if (new_direction < 0)
        new_direction += 2*M_PI;
    direction = new_direction;
}

double Player::projectDirection(double direction_change_alpha) {
    if (direction + direction_change_alpha < 0)
        return (2*M_PI-direction+direction_change_alpha);
    if (direction + direction_change_alpha > 2*M_PI)
        return (direction + direction_change_alpha - 2*M_PI);
    return direction+direction_change_alpha;
}