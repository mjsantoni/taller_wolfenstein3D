//
// Created by andy on 23/1/21.
//

#include "client/window_drawer.h"

#define PROJECTION_PLANE_width 320

SDL_Texture* WindowDrawer::drawWall(ObjectInfo& object_info,
                                    Area& image_area) {
    SdlTexture sdl_texture(object_info.getImagePath());
    SDL_Texture* image = sdl_texture.loadTexture(renderer, image_area);
    image_area.setX((int) (object_info.getHitGridPos() *image_area.getWidth()));
    image_area.setWidth(image_area.getWidth()/map_grid_size);
    return image;
}

void WindowDrawer::putTextureAt(SDL_Texture* texture, Area src, Area dest) {
    SDL_Rect sdlSrc = {
            src.getX(), src.getY(), src.getWidth(), src.getHeight()
    };
    // donde se pega, y si hay diferencia de dimensiones
    SDL_Rect sdlDest = {
            dest.getX(), dest.getY(), dest.getWidth(), dest.getHeight()
    };
    SDL_RenderCopy(renderer, texture, &sdlSrc, &sdlDest);
}

SDL_Texture* WindowDrawer::drawImage(ObjectInfo& object_info,
                                      Area& image_area) {
    SdlTexture sdl_texture(object_info.getImagePath());
    SDL_Texture* image = sdl_texture.loadTexture(renderer, image_area);
    return image;
    //printf("Se copiara una pared desde: (%d, %d) con ancho de %d y altura de %d\n", image_area.getX(), image_area.getY(), image_area.getWidth(), image_area.getHeight());
}


