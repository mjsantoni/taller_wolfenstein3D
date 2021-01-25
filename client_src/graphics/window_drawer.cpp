//
// Created by andy on 23/1/21.
//

#include "client/window_drawer.h"

#define PROJECTION_PLANE_width 320

void WindowDrawer::initialize(SDL_Renderer* window_renderer,
                               int window_width,
                               int window_height) {
    renderer = window_renderer;
    this->window_width = window_width;
    this->window_height = window_height;
    this->width_prop = double (window_width) / PROJECTION_PLANE_width;
}

void WindowDrawer::drawPlayersWeapon(int weapon_number) {
    ObjectInfo object_info = info_provider.getMapInfoForObject(weapon_number);
    Area image_area;
    SDL_Texture* texture = drawPlayersWeapon(object_info, image_area);
    Area screen_area = assembleScreenWeaponArea(object_info);
    putTextureAt(texture, image_area, screen_area);
    SDL_DestroyTexture(texture);
}

SDL_Texture* WindowDrawer::drawPlayersWeapon(ObjectInfo& o_i,
                                              Area& image_area) {
    SdlSprite sdl_sprite(o_i.getImagePath(), o_i.getImageWidth(),
                         o_i.getImageHeight(), o_i.getSpriteCols(),
                         o_i.getSpriteRows(), o_i.getSpriteHPadding(),
                         o_i.getSpriteVPadding());
    SDL_Texture* image = sdl_sprite.loadTexture(renderer, image_area,
                                                o_i.getSpriteAnimationNo());
    return image;
}

SDL_Texture* WindowDrawer::drawWall(ObjectInfo& object_info,
                                    Area& image_area) {
    SdlTexture sdl_texture(object_info.getImagePath());
    SDL_Texture* image = sdl_texture.loadTexture(renderer, image_area);
    image_area.setX((int) (object_info.getHitGridPos() *image_area.getWidth()));
    image_area.setWidth(image_area.getWidth()/map_grid_size);
    return image;
}

Area WindowDrawer::assembleScreenWeaponArea(ObjectInfo& object_info) {
    int weapon_window_width = (int) (object_info.getObjectWidth() *
            window_width);
    int weapon_window_height = (int) (object_info.getObjectHeight() *
            window_height);
    int starting_y_pos = window_height - weapon_window_height;
    int starting_x_pos = (window_width - weapon_window_width) / 2;
    Area screen_area(starting_x_pos, starting_y_pos, weapon_window_width,
                     weapon_window_height);
    return screen_area;
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

Area WindowDrawer::assembleScreenArea(int ray_no, ObjectInfo& drawing_info) {
    int width_factor = window_width/PROJECTION_PLANE_width;
    int distance = (int) drawing_info.getHitDistance();
    int col_height = findColumnHeight(distance);
    int col_starting_point = findColumnStartingPoint(col_height);
    Area screen_area(
            ray_no*width_factor,col_starting_point, width_factor, col_height
    );
    //printf("Rayo %d:Se coloca una pared a distancia %d, en (%d, %d), con un ancho de %d y altura de %d\n",
    //ray_no, distance, ray_no*width_factor, col_starting_point, width_factor, col_height);
    return screen_area;
}

int WindowDrawer::findColumnHeight(int distance) {
    auto height_proportion = (double) map_grid_size/distance;
    return (int) (height_proportion*255);
}

int WindowDrawer::findColumnStartingPoint(int col_height) {
    return (window_height - col_height)/2;
}

SDL_Texture* WindowDrawer::drawImage(ObjectInfo& object_info,
                                      Area& image_area) {
    SdlTexture sdl_texture(object_info.getImagePath());
    SDL_Texture* image = sdl_texture.loadTexture(renderer, image_area);
    return image;
    //printf("Se copiara una pared desde: (%d, %d) con ancho de %d y altura de %d\n", image_area.getX(), image_area.getY(), image_area.getWidth(), image_area.getHeight());
}


