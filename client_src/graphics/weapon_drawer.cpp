//
// Created by andy on 10/2/21.
//

#include "client/graphics/weapon_drawer.h"

#define EQ_WEAPON_DELTA 22

WeaponDrawer::WeaponDrawer(SdlWindow& _window,
                           ObjectInfoProvider& _info_provider,
                           TextureManager& _texture_manager) :
                           window(_window),
                           info_provider(_info_provider),
                           texture_manager(_texture_manager) {

}

void WeaponDrawer::drawPlayersEquippedWeapon(int weapon_number) {
    int object_type = weapon_number + EQ_WEAPON_DELTA;
    ObjectInfo object_info = info_provider.getObjectInfo(weapon_number
                                                         + EQ_WEAPON_DELTA);
    SDL_Texture* texture =
            texture_manager.getImageFromObjectType(object_type);
    Area image_area = texture_manager.getAreaForWeapon(object_type, 0);
    Area screen_area = assembleScreenWeaponArea(object_info);
    window.loadImage(texture, image_area, screen_area);
}

SDL_Texture* WeaponDrawer::getWeaponSprite(ObjectInfo& object_info,
                                           Area& image_area) {
    SdlSprite sprite(object_info);
    SDL_Texture* image = sprite.loadTexture(window.getRenderer(), image_area,
                                            object_info.getSpriteAnimationNo());
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

void WeaponDrawer::displayPlayerAttacking(int weapon_number) {
    ObjectInfo object_info = info_provider.getObjectInfo(weapon_number
                                                         + EQ_WEAPON_DELTA);
    int sprite_animation_no =
            ImageManager::getAttackingAnimationForWeapon(weapon_number);
    object_info.setSpriteAnimationNo(sprite_animation_no);
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

