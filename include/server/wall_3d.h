//
// Created by andy on 28/11/20.
//

#ifndef TP_WOLFENSTEIN_CLIENT_WALL_H
#define TP_WOLFENSTEIN_WALL_3D_H

#include "client/sdl_3D_texture.h"
#include "positionable.h"

class Wall_3d : public Positionable {
public:
    Wall_3d(std::string image_name);
    //SDL_Texture* getImage(SDL_Renderer* renderer, Area& src_area);
    //SDL_Texture* getImageForColumn(SDL_Renderer* renderer, Area& src_area);
};


#endif //TP_WOLFENSTEIN_CLIENT_WALL_H
