#include <functional>
#include "server/game/player.h"
#include "server/entities/gun.h"
#include <iostream>
#include <ctgmath>

Player::Player(std::string _name, int _id, int _max_bullets, int _max_hp, int _bullets) :
                                    name(_name),
                                    id(_id),
                                    knife(Gun("knife", -1, 0, 0, 1, 25)),
                                    pistol(Gun("pistol", -1, 1, 2, 0.75, 100)),
                                    angle(0),
                                    equipped_weapon(pistol),
                                    max_hp(_max_hp),
                                    hp(_max_hp),
                                    max_bullets(_max_bullets),
                                    bullets(_bullets) {
    guns.push_back(knife);
    guns.push_back(pistol);
}

std::string Player::getPlayerName() {return std::ref(name);}

Gun& Player::getGun() { return equipped_weapon; }

void Player::changeGun(int hotkey) {
    equipped_weapon = guns[hotkey];
    std::cout << "Cambie de arma a: " << equipped_weapon.getType() << "\n";
    std::cout << "Tiene precision: " << equipped_weapon.getPrecision() << "\n";
}


void Player::pickUpKey(Key key) { keys.push(key); }

int Player::getID() { return id; }

bool Player::useKey() {
    if (!areAnyKeysLeft()) return false;
    Key key = keys.front();
    keys.pop();
    return true;
}

bool Player::areAnyKeysLeft() {
    return !keys.empty();
}

void Player::addHp(int hp_given) {
    if (hp + hp_given >= max_hp) hp = max_hp;
    else hp += hp_given;
    std::cout << "Agregue hp, ahora tengo: " << hp << "\n";
}

void Player::addPoints(int points_given) {
    points += points_given;
    std::cout << "Agregue puntos, ahora tengo: " << points << "\n";
}

void Player::addGun(Gun gun) {
    guns.push_back(gun); //hay que ver donde va, deberia ser en [id]
    std::cout << "Agregue arma, una: " << gun.getType() << "\n";
}

void Player::addBullets(int added_bullets) {
    if (bullets + added_bullets >= max_bullets) bullets = max_bullets;
    else bullets += added_bullets;
    std::cout << "Agregue balas, ahora tengo: " << bullets << "\n";
}

void Player::addKey(Key key) {
    keys.push(key);
}

void Player::reduceAmmo() {
    std::cout << "----------------\n";
    std::cout << "Soy el player: " << id << "\n";
    std::cout << "Tenia (balas): " << bullets << "\n";
    bullets--;
    std::cout << "Ahora tengo (balas): " << bullets << "\n";
}

bool Player::reduceHP(int damage) {
    std::cout << "----------------\n";
    std::cout << "Soy el player: " << id << "\n";
    std::cout << "Tenia (hp): " << hp << "\n";
    hp -= damage;
    std::cout << "Me dispararon y ahora tengo (hp): " << hp << "\n";
    return hp > 0;
}

double Player::getAngle() {return angle;}

void Player::addAngle(double _angle) {
    if ((angle + _angle) > (2*M_PI)) {
        angle = (angle + _angle - 2*M_PI);
    } else {
        angle += _angle;
    }
}

bool Player::isFullHP() {
    return hp == max_hp;
}

bool Player::canPickUpBlood() {
    return hp < 11;
}

bool Player::hasMaxBullets() {
    return bullets >= max_bullets;
}

bool Player::hasGun(std::string gun_type) {
    for (auto& gun : guns) {
        if (gun.getType() == gun_type) return true;
    }
    return false;
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


