#include <functional>
#include "server/game/player.h"
#include "server/entities/gun.h"
#include <iostream>


Player::Player(std::string _name, int _id) :
                                    name(_name),
                                    id(_id),
                                    knife(Gun("knifebienturro",0,0,0,100)),
                                    pistol(Gun("pistol",0,1,2,75)),
                                    equipped_weapon(pistol) {
    guns.push_back(knife);
    guns.push_back(pistol);
}

std::string Player::getPlayerName() {return std::ref(name);}

Gun Player::getGun() {return equipped_weapon;}

void Player::changeGun(int hotkey) {
    equipped_weapon = guns[hotkey];
    std::cout << "Cambie de arme a: " << equipped_weapon.getType() << "\n";
}



void Player::pickUpKey(Key key) {keys.push(key);}

int Player::getID() {return id;}

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
    std::cout << "Player pickeo: " << item.getCategory() << "\n";
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
    guns.push_back(gun); //hay que ver donde va, deberia ser en [id]
    std::cout << "Agregue una: " << gun.getId() << "\n";
}

void Player::addBullets(int added_bullets) {
    bullets += added_bullets;
    std::cout << "Agregue balas, ahora tengo: " << bullets << "\n";
}

void Player::addKey(Key key) {
    keys.push(key);
}

void Player::reduceAmmo() {
    std::cout << "Soy el player: " << id << "\n";
    std::cout << "Tenia (balas): " << bullets << "\n";
    bullets--;
    std::cout << "Ahora tengo (balas): " << bullets << "\n";

}

void Player::reduceHP(int damage) {
    std::cout << "Soy el player: " << id << "\n";
    std::cout << "Tenia (hp): " << hp << "\n";
    hp -= damage;
    std::cout << "Me dispararon y ahora tengo (hp): " << hp << "\n";
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


