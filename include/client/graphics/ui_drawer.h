//
// Created by andy on 3/1/21.
//

#ifndef TP_WOLFENSTEIN_UI_DRAWER_H
#define TP_WOLFENSTEIN_UI_DRAWER_H

#define WEAPON_ICON_DELTA UI_KNIFE_ICON-1

#include <zconf.h>
#include <string>
#include "area.h"
#include "client/game/client_player.h"
#include "client/object_info_provider.h"
#include "sdl_window.h"
#include "sdl_message.h"
#include <client/graphics/sdl_message.h>
#include <client/graphics/sdl_sprite.h>
#include "message_parameters.h"

class UIDrawer {
 private:
  SdlWindow& window;
    ObjectInfoProvider& info_provider;
  int starting_point;
  int window_height;
  int ui_height;
  int width;
  int box_starting_point = 0;
  int text_starting_point = 0;
  int h_padding = 10;
  int v_padding = 0;
  void renderMessage(const std::string& message_text, Area& msg_area,
                     Area& screen_area, MessageParameters message_parameters);
  void drawPlayersKeys(int players_level);
  void drawPlayersScore(int players_score);
  void drawPlayersLives(int players_lives);
  void drawPlayersHealth(int players_health);
  void drawPlayersAmmo(int players_ammo);
  void drawPlayersImage(double health_ratio);
  void drawPlayersWeaponIcon(int player_weapon);

  void drawBox(const std::string& message, int value);
  void fillArea(Area area, int r, int g, int b, int a);
  void fillAreaWithBorder(Area area, int r, int g, int b, int a);
  void fillTextArea(TTF_Font* font, const std::string& message,
                    Area& screen_area);
  void putTextureAt(SDL_Texture* texture, Area src, Area dest);

 public:
  UIDrawer(ObjectInfoProvider& _info_provider, SdlWindow& _window);
  void setDimensions(int _starting_point, int _height, int _width);
  void drawPlayerUI(ClientPlayer& player);
  void renderDeadMode();
};

#endif //TP_WOLFENSTEIN_UI_DRAWER_H
