//
// Created by andy on 28/11/20.
//

#include "server/wall_3d.h"

Wall_3d::Wall_3d(std::string image_name) : Positionable("Wall", 1, false,
                                                    std::move(image_name),""){

}

/*
SDL_Texture* Wall_3d::getImage(SDL_Renderer* renderer, Area& src_area) {
    return image.load3DTexture(renderer, src_area);
}

SDL_Texture* Wall_3d::getImageForColumn(SDL_Renderer* renderer, Area& src_area){
    return image.load3DTextureForColumn(renderer, src_area);
}
 */