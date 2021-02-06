//
// Created by andy on 25/11/20.
//

#include <functional>
#include "client/game/client_player.h"

ClientPlayer::ClientPlayer(std::string name) :  name(std::move(name)) {
}

std::string ClientPlayer::getPlayerName() {
    return std::ref(name);
}

double ClientPlayer::getDirection() {
    return direction;
}

void ClientPlayer::updateDirection(double offset) {
    double new_direction = direction + offset;
    if (new_direction >= 2*M_PI)
        new_direction -= 2*M_PI;
    if (new_direction < 0)
        new_direction += 2*M_PI;
    direction = new_direction;
}

double ClientPlayer::projectDirection(double direction_change_alpha) {
    if (direction + direction_change_alpha < 0)
        return (2*M_PI+(direction+direction_change_alpha));
    if (direction + direction_change_alpha > 2*M_PI)
        return (direction + direction_change_alpha - 2*M_PI);
    return direction+direction_change_alpha;
}

int ClientPlayer::getEquippedWeapon() {
    return equipped_weapon;
}

int ClientPlayer::getLevel() {
    return level;
}

int ClientPlayer::getScore() {
    return score;
}

int ClientPlayer::getLives() {
    return lives;
}

int ClientPlayer::getHealth() {
    return health;
}

int ClientPlayer::getAmmo() {
    return ammo;
}

void ClientPlayer::updatePosition(int new_x, int new_y) {
    std::cout << "Actualizo pos\n";
    map_position = {new_x, new_y};
}

int ClientPlayer::getId() {
    return id;
}

void ClientPlayer::setId(int new_id) {
    id = new_id;
}

void ClientPlayer::updateScore(int extra_points) {
    score += extra_points;
}

void ClientPlayer::updateHealth(int health_delta) {
    health += health_delta;
    health = (health < 0) ? 0 : health;
    health = (health > max_health) ? max_health : health;
}

void ClientPlayer::updateAmmo(int ammo_delta) {
    ammo += ammo_delta;
    ammo = (ammo < 0) ? 0 : ammo;
    ammo = (ammo > max_ammo) ? max_ammo : ammo;
}

void ClientPlayer::updateKeys(int keys_delta) {
    keys += keys_delta;
    keys = (keys < 0) ? 0 : keys;
}

void ClientPlayer::respawn() {
    map_position = respawn_position;
}

void ClientPlayer::changeWeapon(int weapon_number) {
    if (!weapons[weapon_number-1])
        return;
    equipped_weapon = weapon_number;
}

std::pair<int, int> ClientPlayer::getMapPosition() {
    return map_position;
}

void ClientPlayer::setMapPosition(std::pair<int, int> new_map_position) {
    map_position = new_map_position;
}

int ClientPlayer::getXPosition() {
    return map_position.first;
}

int ClientPlayer::getYPosition() {
    return map_position.second;
}
