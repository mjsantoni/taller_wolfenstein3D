#include <functional>
#include "server/game/player.h"
#include "server/entities/gun.h"
#include <iostream>
#include <ctgmath>

#define EXTRA_GUN_VECTOR_SIZE 1

Player::Player(std::string _name, int _id, int _max_bullets, int _max_hp, int _bullets) :
                                    name(_name),
                                    id(_id),
                                    angle(0),
                                    max_hp(_max_hp),
                                    hp(_max_hp),
                                    max_bullets(_max_bullets),
                                    bullets(_bullets) {
    // Los parametros de las guns default deberian venir por config (parametro)
    guns.resize(TOTAL_GUNS + EXTRA_GUN_VECTOR_SIZE);
    guns[KNIFE] = Gun("knife", -1, 1, 0, 1, 25);
    guns[PISTOL] = Gun("pistol", -1, 1, 2, 0.75, 100);
    equipped_weapon = guns[PISTOL];
}

/* GETTERS */
std::string Player::getPlayerName() { return name; }

Gun& Player::getGun() { return equipped_weapon; }

int Player::getID() { return id; }

double Player::getAngle() { return angle; }

void Player::changeGun(int hotkey) {
    previous_weapon = getGunHotkey(equipped_weapon.getType());
    equipped_weapon = guns[hotkey];
    std::cout << "Cambie de arma a: " << equipped_weapon.getType() << "\n";
    std::cout << "Tiene precision: " << equipped_weapon.getPrecision() <<
    " y tiene rango: " << equipped_weapon.getRange() << "\n";
}

/* ADDERS */
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
    guns[getGunHotkey(gun.getType())] = gun;
    std::cout << "Agregue arma, una: " << gun.getType() << "\n";
}

void Player::addBullets(int added_bullets) {
    if (bullets == 0) {
        std::cout << "Tenia 0 balas, y un " << equipped_weapon.getType()
        << " equipado. Vuelvo a arma anterior.\n";
        changeGun(previous_weapon);
    }
    if (bullets + added_bullets >= max_bullets) bullets = max_bullets;
    else bullets += added_bullets;
    std::cout << "Agregue balas, ahora tengo: " << bullets << "\n";
}

void Player::addKey(Key key) {
    keys.push(key);
}

void Player::addAngle(double _angle) {
    if ((angle + _angle) > (2*M_PI)) {
        angle = (angle + _angle - 2*M_PI);
    } else {
        angle += _angle;
    }
}

/* REDUCERS */
void Player::reduceAmmo() {
    if (equipped_weapon.getType() == "knife") {
        std::cout << "Tengo equipado un knife, no resto balas\n";
        return;
    }
    std::cout << "----------------\n";
    std::cout << "Soy el player: " << id << "\n";
    std::cout << "Tenia (balas): " << bullets << "\n";
    bullets--;
    std::cout << "Ahora tengo (balas): " << bullets << "\n";
    if (bullets == 0) {
        std::cout << "Me quede sin balas cambio a: " << equipped_weapon.getType() << "\n";
        previous_weapon = getGunHotkey(equipped_weapon.getType());
        changeGun(KNIFE);
    }
}

bool Player::reduceHP(int damage) {
    std::cout << "----------------\n";
    std::cout << "Soy el player: " << id << "\n";
    std::cout << "Tenia (hp): " << hp << "\n";
    hp -= damage;
    std::cout << "Me dispararon y ahora tengo (hp): " << hp << "\n";
    return hp <= 0;
}

/* OTHERS (CHECKERS) */
bool Player::isFullHP() const { return hp == max_hp; }

bool Player::canPickUpBlood() const { return hp < 11; }

bool Player::hasMaxBullets() const { return bullets >= max_bullets; }

bool Player::noAmmoLeft() const { return bullets <= 0; }

bool Player::hasGun(std::string gun_type) {
    for (auto& gun : guns) {
        if (gun.getType() == gun_type) return true;
    }
    return false;
}

/* KEYS */
void Player::pickUpKey(Key key) { keys.push(key); }

bool Player::useKey() {
    if (!areAnyKeysLeft()) return false;
    Key key = keys.front();
    keys.pop();
    return true;
}

bool Player::areAnyKeysLeft() {
    return !keys.empty();
}

int Player::getGunHotkey(const std::string& type) {
    if (type == "chain_gun") return CHAIN_GUN;
    else if (type == "machine_gun") return MACHINE_GUN;
    else if (type == "rpg_gun") return RPG_GUN;
    else if (type == "pistol") return PISTOL;
    else if (type == "knife") return KNIFE;
    else return 0; // Aca explotaria
}

/*
bool Player::die() {
    lives--;
    if (lives > 0) return true; // respawnAtOriginalLoc()
    else return false;
}
*/


