#ifndef TP_WOLFENSTEIN_PLAYER_H
#define TP_WOLFENSTEIN_PLAYER_H

#include <string>
#include "positionable.h"
#include "server/entities/gun.h"
#include "server/entities/key.h"
#include <queue>
#include <vector>
#include "default_weapon.h"

class Player {
private:
    std::string name;
    int id;
    int bullets = 100;
    int hp = 100;
    int points = 0;
    int lives;
    std::vector<Gun> dropable;
    //DefaultWeapon knife;
    //DefaultWeapon pistol;
    std::queue<Key> keys;
    //DefaultWeapon& equipped_weapon;
    //Gun& equipped_dropable_weapon;

    //double direction = M_PI/4;

public:
    Player(std::string _name, int _id); //parametros de config como hp faltan
    std::string getPlayerName();
    bool areAnyKeysLeft();
    bool useKey();
    void pickUpKey(Key key);

    void addHp(int hp_given);
    void addPoints(int points_given);
    void addGun(Gun gun);
    void addBullets(int added_bullets);
    void addKey(Key key);

    int getID();

    void equipWeapon(std::string id);
    void pickUpItem(Positionable item);


    void reduceAmmo();

    void reduceHP(int i);
};

#endif //TP_WOLFENSTEIN_CLIENT_PLAYER_H
