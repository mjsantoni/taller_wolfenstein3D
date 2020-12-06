//
// Created by andy on 28/11/20.
//

#include <SDL_image.h>
#include "client/Sdl3DTexture.h"
#include "client/SdlException.h"

Sdl3DTexture::Sdl3DTexture(std::string file_name) :
                            SdlTexture(std::move(file_name)){
}

SDL_Texture * Sdl3DTexture::load3DTexture(SDL_Renderer *renderer,
                                          Area &srcArea) {
    SDL_Texture* new_texture = IMG_LoadTexture(renderer, file_name.c_str());
    if (!new_texture)
        throw SdlException("Error en la carga de la textura", SDL_GetError());
    texture = new_texture;
    getDimensions(new_texture);
    fillDimensions(srcArea);
    return new_texture;
}

void Sdl3DTexture::fillDimensions(Area &area) {
    area.setY(0);
    int original_x = area.getX();
    int x = original_x%width;
    area.setX(x);
    int width_proportion = area.getWidth();
    area.setWidth(2);
    area.setHeight(height);
}

SDL_Texture* Sdl3DTexture::load3DTextureForColumn(SDL_Renderer* renderer,
                                                  Area& src_area) {
    SDL_Texture* new_texture = IMG_LoadTexture(renderer, file_name.c_str());
    if (!new_texture)
        throw SdlException("Error en la carga de la textura", SDL_GetError());
    texture = new_texture;
    getDimensions(new_texture);
    fillDimensions(src_area);
    return new_texture;
}
