#ifndef TP_WOLFENSTEIN_PLAYER_H
#define TP_WOLFENSTEIN_PLAYER_H

#include <string>
#include "positionable.h"
#include "gun.h"
#include "key.h"
#include <queue>
#include <vector>
#include "default_weapon.h"

class Player {
private:
    std::string name;
    int bullets;
    int hp;
    int points;
    int lives;
    std::vector<Gun> dropable;
    //DefaultWeapon knife;
    //DefaultWeapon pistol;
    std::queue<Key> keys;
    //DefaultWeapon& equipped_weapon;
    //Gun& equipped_dropable_weapon;


    //double direction = M_PI/4;

public:
    Player(std::string name);
    std::string getPlayerName();
    bool areAnyKeysLeft();
    bool useKey();
    void pickUpKey(Key key);

    void equipWeapon(std::string type);

    void pickUp(Positionable item);
};

/*
      double getDirection();
      void updateDirection(double offset);
      double projectDirection(double direction_change_alpha);
      */
#endif //TP_WOLFENSTEIN_CLIENT_PLAYER_H
