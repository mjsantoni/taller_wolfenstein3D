//
// Created by andy on 10/2/21.
//

#include "client/graphics/weapon_drawer.h"

#define EQ_WEAPON_DELTA SCREEN_WEAPON_KNIFE-1

WeaponDrawer::WeaponDrawer(SdlWindow& _window,
                           ObjectInfoProvider& _info_provider,
                           TextureManager& _texture_manager) :
    window(_window),
    info_provider(_info_provider),
    texture_manager(_texture_manager) {

}

void WeaponDrawer::drawPlayersWeapon(int weapon_number, int sprite_no) {
  int object_type = weapon_number + EQ_WEAPON_DELTA;
  ObjectInfo object_info = info_provider.getObjectInfo(weapon_number
                                                           + EQ_WEAPON_DELTA);
  auto* texture = (SdlSprite*)
      texture_manager.getTextureFromObjectType(object_type);
  if (sprite_no > 3)
    sprite_no = 3;
  Area screen_area = assembleScreenWeaponArea(object_info);
  texture->render(screen_area, sprite_no);
}

Area WeaponDrawer::assembleScreenWeaponArea(ObjectInfo& object_info) {
  int weapon_window_width = (int) (object_info.getObjectWidth() * weapon_width);
  int weapon_window_height = (int) (object_info.getObjectHeight()
      * window_height);
  int starting_y_pos = starting_point - weapon_window_height;
  int starting_x_pos = (weapon_width - weapon_window_width) / 2;
  Area screen_area(starting_x_pos, starting_y_pos, weapon_window_width,
                   weapon_window_height);
  return screen_area;
}

void WeaponDrawer::setDimensions(int _starting_point,
                                 int _width) {
  starting_point = _starting_point;
  window_height = (int) (_starting_point / 0.8);
  weapon_width = _width;
}

