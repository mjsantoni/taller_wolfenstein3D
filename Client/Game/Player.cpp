//
// Created by andy on 25/11/20.
//

#include <functional>
#include "Player.h"

Player::Player(std::string name) :  name(std::move(name)) {
}

std::string Player::getPlayerName() {
    return std::ref(name);
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