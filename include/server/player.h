#ifndef TP_WOLFENSTEIN_PLAYER_H
#define TP_WOLFENSTEIN_PLAYER_H

#include <string>
#include "client/sdl_texture.h"
#include "client/sdl_sprite.h"
#include "positionable.h"

//Mauro
#include "key.h"
#include <queue>

class Player {
public:
    Player(std::string name);
    std::string getPlayerName();
    double getDirection();
    void updateDirection(double offset);
    double projectDirection(double direction_change_alpha);

private:
    std::string name;
    double direction = M_PI/4;

    //Mauro
    //std::string name;
    int bullets;
    int hp;
    int points;
    int lives;
    //WeaponInventory ?;
    std::queue<Key> keys;
};


#endif //TP_WOLFENSTEIN_PLAYER_H
