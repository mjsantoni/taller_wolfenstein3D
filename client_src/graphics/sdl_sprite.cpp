//
// Created by andy on 26/11/20.
//

#include <SDL_image.h>
#include "client/graphics/sdl_sprite.h"

SdlSprite::SdlSprite(std::string file_name, int width, int height, int cols,
                     int rows, int h_padding, int v_padding) : whole_width(width),
                     whole_height(height), cols(cols), rows(rows),
                     h_padding(h_padding), v_padding(v_padding),
                     SdlTexture(std::move(file_name)) {
    loadIndividualDimensions();
}

SDL_Texture* SdlSprite::loadNextTexture(SDL_Renderer *renderer, Area& srcArea) {
    SDL_Texture* new_texture = IMG_LoadTexture(renderer, file_name.c_str());
    if (!new_texture)
        throw SdlException("Error en la carga de la textura", SDL_GetError());
    if (!already_loaded) {
        loadIndividualDimensions();
        already_loaded = true;
    }
    texture = new_texture;
    //fillDimensions(srcArea);
    current_pos++;
    return new_texture;
}

void SdlSprite::loadIndividualDimensions() {
    each_img_width = whole_width/cols-h_padding/2;
    each_img_height = whole_height/rows-v_padding/2;
    int x = 0;
    int y = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            Area area(x, y, each_img_width, each_img_height);
            dimensions.push_back(area);
            if (dimensions.size() >= 5)
                return;
            x+= h_padding/2 + each_img_width;
        }
        x = 0;
        y+= v_padding/2 + each_img_height;
    }
}

SDL_Texture* SdlSprite::loadTexture(SDL_Renderer *renderer,
                                    Area &srcArea,
                                    int sprite_number) {
    SDL_Texture* new_texture = IMG_LoadTexture(renderer, file_name.c_str());
    if (!new_texture)
        throw SdlException("Error en la carga de la textura", SDL_GetError());

    Area image_area = dimensions[sprite_number];
    fillDimensions(image_area, srcArea);
    texture = new_texture;
    return new_texture;
}

void SdlSprite::fillDimensions(Area& source_area, Area& empty_area) {
    empty_area.setX(source_area.getX());
    empty_area.setY(source_area.getY());
    empty_area.setWidth(source_area.getWidth());
    empty_area.setHeight(source_area.getHeight());
}
