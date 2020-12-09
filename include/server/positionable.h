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
    //Andy
    Positionable(std::string object_name, int object_type, bool is_sprite,
                 std::string image_name, std::string unique_name);
    int getObjectType();
    bool isSprite();
    int getCurrentImageNumber();
    std::string getTextureName();
    Positionable();
    virtual std::string getObjectName();

    //Mauro
    Positionable(std::string _object_type, std::string _sprite_path,
                 int _id, bool _is_obstructive);

protected:
    //Andy stuff
    std::string object_name;
    //int object_type;
    bool is_sprite;
    int sprite_image_number = 0;
    std::string texture_name;
    std::string unique_name;

    //Mauro stuff
    std::string object_type;
    std::string sprite_path;
    int id;
    bool is_obstructive;
};


#endif //TP_WOLFENSTEIN_POSITIONABLE_H
