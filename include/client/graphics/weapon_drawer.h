//
// Created by andy on 10/2/21.
//

#ifndef TP_WOLFENSTEIN_WEAPON_DRAWER_H
#define TP_WOLFENSTEIN_WEAPON_DRAWER_H

#include <client/object_info.h>
#include <client/graphics/area.h>
#include <SDL_render.h>
#include <client/graphics/sdl_sprite.h>
#include <client/object_info_provider.h>
#include "sdl_window.h"
#include "texture_manager.h"
#include <client/game/image_manager.h>

class WeaponDrawer {
private:
    SdlWindow& window;
    ObjectInfoProvider& info_provider;
    TextureManager& texture_manager;
    int weapon_width;
    int window_width;
    int window_height;
    int starting_point;
public:
    WeaponDrawer(SdlWindow &_window, ObjectInfoProvider &_info_provider,
                 TextureManager& _texture_manager);
    void drawPlayersWeapon(int weapon_number, int sprite_no);
    Area assembleScreenWeaponArea(ObjectInfo& object_info);
    void displayPlayerAttacking(int weapon_number);
    void displayPlayerStopShooting(int weapon_number);
    void setDimensions(int _starting_point, int _width);
};


#endif //TP_WOLFENSTEIN_WEAPON_DRAWER_H
