//
// Created by andy on 26/11/20.
//

#include "client/SdlTexture.h"
#include "client/SdlException.h"
#include <SDL_image.h>

SdlTexture::SdlTexture(std::string file_name) : file_name(file_name){
}

SdlTexture::~SdlTexture() {
    //SDL_DestroyTexture(texture);
}

SDL_Texture* SdlTexture::loadTexture(SDL_Renderer* renderer, Area& srcArea) {
    SDL_Texture* new_texture = IMG_LoadTexture(renderer, file_name.c_str());
    if (!new_texture)
        throw SdlException("Error en la carga de la textura", SDL_GetError());
    getDimensions(new_texture);
    texture = new_texture;
    fillDimensions(srcArea);
    return new_texture;
}

SDL_Texture* SdlTexture::getTexture() {
    return texture;
}

void SdlTexture::getDimensions(SDL_Texture* new_texture) {
    SDL_QueryTexture(new_texture, nullptr, nullptr, &width, &height);
}

void SdlTexture::fillDimensions(Area &srcArea) {
    srcArea.setWidth(width);
    srcArea.setHeight(height);
}

Area SdlTexture::getArea() {
    Area my_area(0, 0, width, height);
    return my_area;
}
