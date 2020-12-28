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
private:
    std::string name;
    double direction = M_PI/2;
};


#endif //TP_WOLFENSTEIN_CLIENT_PLAYER_H
