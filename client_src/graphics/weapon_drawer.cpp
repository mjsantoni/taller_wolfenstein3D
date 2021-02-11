//
// Created by andy on 10/2/21.
//

#include "client/graphics/weapon_drawer.h"

#define EQ_WEAPON_DELTA 21

WeaponDrawer::WeaponDrawer(SdlWindow& _window,
                           ObjectInfoProvider& _info_provider) :
                           window(_window),
                           info_provider(_info_provider) {

}

void WeaponDrawer::drawPlayersEquippedWeapon(int weapon_number) {
    ObjectInfo object_info = info_provider.getObjectInfo(weapon_number
                                                         + EQ_WEAPON_DELTA);
    Area image_area;
    SDL_Texture* texture = getWeaponSprite(object_info, image_area);
    Area screen_area = assembleScreenWeaponArea(object_info);
    window.loadImage(texture, image_area, screen_area);
    SDL_DestroyTexture(texture);
}

SDL_Texture* WeaponDrawer::getWeaponSprite(ObjectInfo& o_i, Area& image_area) {
    SdlSprite sdl_sprite(o_i.getImagePath(), o_i.getImageWidth(),
                         o_i.getImageHeight(), o_i.getSpriteCols(),
                         o_i.getSpriteRows(), o_i.getSpriteHPadding(),
                         o_i.getSpriteVPadding());
    SDL_Texture* image = sdl_sprite.loadTexture(window.getRenderer(), image_area,
                                                o_i.getSpriteAnimationNo());
    return image;
}

Area WeaponDrawer::assembleScreenWeaponArea(ObjectInfo& object_info) {
    int weapon_window_width = (int) (object_info.getObjectWidth() * width);
    int weapon_window_height = (int) (object_info.getObjectHeight()
                                      * window_height);
    int starting_y_pos = starting_point - weapon_window_height;
    int starting_x_pos = (width - weapon_window_width) / 2;
    Area screen_area(starting_x_pos, starting_y_pos, weapon_window_width,
                     weapon_window_height);
    return screen_area;
}

void WeaponDrawer::displayPlayerShooting(int weapon_number) {
    ObjectInfo object_info = info_provider.getObjectInfo(weapon_number
                                                         + EQ_WEAPON_DELTA);
    object_info.setSpriteAnimationNo(2);
    Area image_area;
    SDL_Texture* texture = getWeaponSprite(object_info, image_area);
    Area screen_area = assembleScreenWeaponArea(object_info);
    window.loadImage(texture, image_area, screen_area);
    SDL_DestroyTexture(texture);
    window.render();
}

void WeaponDrawer::displayPlayerStopShooting(int weapon_number) {
    ObjectInfo object_info = info_provider.getObjectInfo(weapon_number
                                                         + EQ_WEAPON_DELTA);
    Area image_area;
    SDL_Texture* texture = getWeaponSprite(object_info, image_area);
    Area screen_area = assembleScreenWeaponArea(object_info);
    window.loadImage(texture, image_area, screen_area);
}

void WeaponDrawer::setDimensions(int _starting_point,
                                 int _width) {
    starting_point = _starting_point;
    window_height = (int) (_starting_point / 0.8);
    width = _width;
}

