//
// Created by andy on 25/11/20.
//

#ifndef TP_WOLFENSTEIN_PLAYER_H
#define TP_WOLFENSTEIN_PLAYER_H

#include <string>
#include "../Graphics/SdlTexture.h"
#include "../Graphics/SdlSprite.h"
#include "Positionable.h"

class Player : public Positionable {
public:
    Player(std::string name, std::string image_path, int rows, int cols);
    std::string getPlayerName();
    SDL_Texture* getImage(SDL_Renderer* renderer, Area& src_area);
    double getDirection();
    void updateDirection(double offset);
    double projectDirection(double direction_change_alpha);
private:
    std::string name;
    SdlSprite image;
    double direction = M_PI/4;
};


#endif //TP_WOLFENSTEIN_PLAYER_H
