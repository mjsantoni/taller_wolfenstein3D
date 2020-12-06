//
// Created by andy on 26/11/20.
//

#ifndef TP_WOLFENSTEIN_SDLTEXTURE_H
#define TP_WOLFENSTEIN_SDLTEXTURE_H


#include <string>
#include <SDL_render.h>
#include "Area.h"

class SdlTexture {
public:
    SdlTexture(std::string file_name);
    ~SdlTexture();
    SDL_Texture* getTexture();
    SDL_Texture* loadTexture(SDL_Renderer* renderer, Area& srcArea);
    Area getArea();
protected:
    std::string file_name;
    int width = 0;
    int height = 0;
    SDL_Texture* texture;

    void getDimensions(SDL_Texture* new_texture);
    virtual void fillDimensions(Area& area);
};


#endif //TP_WOLFENSTEIN_SDLTEXTURE_H
