//
// Created by andy on 28/11/20.
//

#ifndef TP_WOLFENSTEIN_CLIENT_WALL_3D_H
#define TP_WOLFENSTEIN_CLIENT_WALL_3D_H


#include "client_positionable.h"
#include "sdl_3D_texture.h"

class ClientWall_3d : public ClientPositionable {
public:
    ClientWall_3d(std::string image_name);
    //SDL_Texture* getImage(SDL_Renderer* renderer, Area& src_area);
    //SDL_Texture* getImageForColumn(SDL_Renderer* renderer, Area& src_area);
};


#endif //TP_WOLFENSTEIN_CLIENT_WALL_3D_H
