//
// Created by andy on 25/11/20.
//

#ifndef TP_WOLFENSTEIN_CLIENT_PLAYER_H
#define TP_WOLFENSTEIN_CLIENT_PLAYER_H

#include <string>
#include "sdl_texture.h"
#include "sdl_sprite.h"
#include "positionable_mock.h"

class ClientPlayer {
public:
    ClientPlayer(std::string name);
    std::string getPlayerName();
    double getDirection();
    void updateDirection(double offset);
    double projectDirection(double direction_change_alpha);
    int getEquippedWeapon();
    int getLevel();
    int getScore();
    int getLives();
    int getHealth();
    int getAmmo();
private:
    std::string name;
    double direction = 5.934119;
    int equipped_weapon = 14;
    int level = 6;
    int score = 10000;
    int lives = 5;
    int health = 100;
    int ammo = 200;
};


#endif //TP_WOLFENSTEIN_CLIENT_PLAYER_H
