#include <functional>
#include "server/player.h"
#include "server/knife.h"
#include "server/pistol.h"
#include "server/machine_gun.h"

Player::Player(std::string name) :  name(std::move(name)){
                                    //knife(Knife()),
                                    //pistol(Pistol()) {
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

