//
// Created by andy on 28/11/20.
//

#include "client/client_wall.h"

ClientWall::ClientWall(std::string image_name) :
        PositionableMock("Wall", 0, false, std::move(image_name), "", 1, 1){ }

/*
SDL_Texture* Wall_3d::getImage(SDL_Renderer* renderer, Area& src_area) {
    return image.load3DTexture(renderer, src_area);
}

SDL_Texture* Wall_3d::getImageForColumn(SDL_Renderer* renderer, Area& src_area){
    return image.load3DTextureForColumn(renderer, src_area);
}
 */