//
// Created by andy on 25/11/20.
//

#ifndef TP_WOLFENSTEIN_POSITIONABLE_H
#define TP_WOLFENSTEIN_POSITIONABLE_H


#include <SDL_render.h>
#include <string>
#include "../Graphics/Area.h"
#include "../Graphics/SdlTexture.h"

class Positionable {
public:
    Positionable(std::string name);

    Positionable();

    virtual std::string getName();
private:
    std::string name;
};


#endif //TP_WOLFENSTEIN_POSITIONABLE_H
