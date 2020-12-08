//
// Created by andy on 25/11/20.
//

#ifndef TP_WOLFENSTEIN_POSITIONABLE_H
#define TP_WOLFENSTEIN_POSITIONABLE_H


#include <SDL_render.h>
#include <string>
#include "client/area.h"
#include "client/sdl_texture.h"

class Positionable {
public:
    Positionable(std::string object_name, int object_type, bool is_sprite,
                 std::string image_name, std::string unique_name);
    int getObjectType();
    bool isSprite();
    int getCurrentImageNumber();
    std::string getTextureName();
    Positionable();

    virtual std::string getObjectName();

protected:
    std::string object_name;
    int object_type;
    bool is_sprite;
    int sprite_image_number = 0;
    std::string texture_name;
    std::string unique_name;
};


#endif //TP_WOLFENSTEIN_POSITIONABLE_H
