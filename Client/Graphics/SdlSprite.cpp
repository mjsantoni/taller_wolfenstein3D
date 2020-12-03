//
// Created by andy on 26/11/20.
//

#include <SDL_image.h>
#include "SdlSprite.h"
#include "../Exceptions/SdlException.h"

SdlSprite::SdlSprite(std::string file_name, int rows, int cols) :
        rows(rows), cols(cols), SdlTexture(std::move(file_name)) {
}

SDL_Texture* SdlSprite::loadNextTexture(SDL_Renderer *renderer, Area& srcArea) {
    SDL_Texture* new_texture = IMG_LoadTexture(renderer, file_name.c_str());
    if (!new_texture)
        throw SdlException("Error en la carga de la textura", SDL_GetError());
    if (!already_loaded) {
        getIndividualDimensions(new_texture);
        already_loaded = true;
    }
    texture = new_texture;
    fillDimensions(srcArea);
    current_pos++;
    return new_texture;
}

void SdlSprite::getIndividualDimensions(SDL_Texture *new_texture) {
    SDL_QueryTexture(new_texture, nullptr, nullptr, &width, &height);
    each_img_width = width/cols;
    each_img_height = height/rows;
    int x = 0;
    int y = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            Area area(x, y, each_img_width, each_img_height);
            dimensions.push_back(area);
            if (dimensions.size() >= 5)
                return;
            x+= each_img_width;
        }
        x = 0;
        y+= each_img_height;
    }
}

void SdlSprite::fillDimensions(Area &srcArea) {
    Area current_image_area = dimensions.at(current_pos%dimensions.size());
    srcArea.setX(current_image_area.getX());
    srcArea.setY(current_image_area.getY());
    srcArea.setWidth(current_image_area.getWidth());
    srcArea.setHeight(current_image_area.getHeight());
}