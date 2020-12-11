//
// Created by andy on 28/11/20.
//

#ifndef TP_WOLFENSTEIN_CLIENT_WALL_H
#define TP_WOLFENSTEIN_CLIENT_WALL_H


#include "client_positionable.h"
#include "sdl_3D_texture.h"

class ClientWall : public ClientPositionable {
public:
    ClientWall(std::string image_name);
    //SDL_Texture* getImage(SDL_Renderer* renderer, Area& src_area);
    //SDL_Texture* getImageForColumn(SDL_Renderer* renderer, Area& src_area);
};


#endif //TP_WOLFENSTEIN_CLIENT_WALL_H
