#include <functional>
#include "server/player.h"
#include "server/knife.h"
#include "server/pistol.h"
#include "server/machine_gun.h"
#include <iostream>
#include <typeinfo>
#include "server/treasure.h"

Player::Player(std::string _name) : name(_name) {
                                    //knife(Knife()),
                                    //pistol(Pistol()) {
    //handler.setPlayer(this);

    //dropable.resize(3);
    //equipped_weapon = pistol;
    //Gun asd = MachineGun();
    //equipped_dropable_weapon = asd;
}

std::string Player::getPlayerName() {
    return std::ref(name);
}

void Player::pickUpKey(Key key) {
    keys.push(key);
}

bool Player::useKey() {
    if (!areAnyKeysLeft()) return false;
    Key key = keys.front();
    keys.pop();
    return true;
}

bool Player::areAnyKeysLeft() {
    return !keys.empty();
}

void Player::pickUpItem(Positionable item) {
    std::cout << "Player pickeo: " << item.getType() << "\n";
}

void Player::addHp(int hp_given) {
    hp += hp_given;
    std::cout << "Mi nueva hp es: " << hp << "\n";
}

void Player::addPoints(int points_given) {
    points += points_given;
    std::cout << "Mis nuevos puntos son: " << points << "\n";
}

void Player::addGun(Gun gun) {
    dropable.push_back(gun); //hay que ver donde va, deberia ser en [id]
    std::cout << "Agregue una: " << gun.getId() << "\n";
}

void Player::addBullets(int added_bullets) {
    bullets += added_bullets;
    std::cout << "Agregue balas, ahora tengo: " << bullets << "\n";
}

void Player::addKey(Key key) {
    keys.push(key);
}

/*
void Player::equipWeapon(std::string type) {
    if (type == "knife") {
        equipped_weapon = knife;
    } else if (type == "pistol") {
        equipped_weapon = pistol;
    } else if (type == "machine_gun"){
        equipped_dropable_weapon = dropable[0];
    } else if (type == "chain_gun"){
        equipped_dropable_weapon = dropable[1];
    } else {
        equipped_dropable_weapon = dropable[2]; //rpg
    }
}*/


/*
bool Player::die() {
    lives--;
    if (lives > 0) return true; // respawnAtOriginalLoc()
    else return false;
}
*/
/*
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
*/

