//
// Created by andy on 3/1/21.
//

#include <SDL_ttf.h>
#include "client/graphics/ui_drawer.h"

#define PLAYER_FACE_SPRITE_IMAGES 8

UIDrawer::UIDrawer(ObjectInfoProvider& _info_provider, SdlWindow& _window) :
    info_provider(_info_provider),
    window(_window) {}

void UIDrawer::setDimensions(int _starting_point,
                             int _ui_height,
                             int _width) {
  starting_point = _starting_point;
  ui_height = _ui_height;
  window_height = starting_point + _ui_height;
  width = _width;
}

void UIDrawer::drawPlayerUI(ClientPlayer& player) {
  TTF_Init();
  Area ui_rect_area(0, starting_point, width, ui_height);
  fillArea(ui_rect_area, 3, 69, 64, 0);
  drawPlayersKeys(player.getKeys());
  drawPlayersScore(player.getScore());
  drawPlayersLives(player.getLives());
  drawPlayersImage(player.getHealthRatio());
  drawPlayersHealth(player.getHealth());
  drawPlayersAmmo(player.getAmmo());
  drawPlayersWeaponIcon(player.getEquippedWeapon());
  /*

   */
  TTF_Quit();
  box_starting_point = 0;
  text_starting_point = 0;
}

void UIDrawer::drawPlayersKeys(int players_keys) {
  drawBox("Keys", players_keys);
}

void UIDrawer::drawPlayersScore(int players_score) {
  drawBox("Score", players_score);
}

void UIDrawer::drawPlayersLives(int players_lives) {
  drawBox("Lives", players_lives);
}

void UIDrawer::drawPlayersHealth(int players_health) {
  drawBox("Health", players_health);
}

void UIDrawer::drawPlayersAmmo(int players_ammo) {
  drawBox("Ammo", players_ammo);
}

void UIDrawer::drawPlayersImage(double health_ratio) {
  text_starting_point += h_padding;
  Area rect_area(box_starting_point, starting_point + 10,
                 width / 10, ui_height - 20);
  fillAreaWithBorder(rect_area, 8, 2, 175, 0);
  Area screen_area(text_starting_point, starting_point + 15,
                   width / 10 - 2 * h_padding, ui_height - 30);
  int sprite_no = (int) (health_ratio * (PLAYER_FACE_SPRITE_IMAGES - 1));
  ObjectInfo face_info = info_provider.getObjectInfo(UI_PLAYER_FACE);
  SdlSprite player_face(window, face_info);
  player_face.render(screen_area, sprite_no);
  box_starting_point += width / 10;
  text_starting_point += width / 10 - h_padding;
}

void UIDrawer::drawPlayersWeaponIcon(int players_weapon) {
  Area rect_area(box_starting_point, starting_point + 10,
                 4 * width / 10, ui_height - 20);
  fillAreaWithBorder(rect_area, 8, 2, 175, 0);
  ObjectInfo object_info = info_provider.getObjectInfo(players_weapon
                                                           + WEAPON_ICON_DELTA);
  SdlTexture weapon_icon(window, object_info.getImagePath());
  Area image_area = weapon_icon.getTextureArea();
  Area screen_area(text_starting_point, starting_point + 15,
                   (4 * width / 10) - 2 * h_padding, ui_height - 30);
  weapon_icon.render(image_area, screen_area);
}

void UIDrawer::drawBox(const std::string& message, int value) {
  text_starting_point += h_padding;
  Area rect_area(box_starting_point, starting_point + 10,
                 width / 10, ui_height - 20);
  fillAreaWithBorder(rect_area, 8, 2, 175, 0);
  Area msg_area;
  Area header_screen_area(text_starting_point, starting_point + 15,
                          width / 10 - 2 * h_padding, ui_height / 2 - 10);
  MessageParameters head_message_parameters(message);
  renderMessage(message, msg_area, header_screen_area, head_message_parameters);

  Area sub_screen_area(text_starting_point, starting_point + 15 +
      ui_height / 2 - 10, width / 10 - 2 * h_padding, ui_height / 2 - 10);
  MessageParameters sub_message_parameters(std::to_string(value));
  renderMessage(std::to_string(value), msg_area, sub_screen_area,
                sub_message_parameters);

  box_starting_point += width / 10;
  text_starting_point += width / 10 - h_padding;
}

void UIDrawer::renderMessage(const std::string& message_text,
                             Area& msg_area,
                             Area& screen_area,
                             MessageParameters message_parameters) {
  SdlMessage message(message_parameters);
  message.renderMessage(window, msg_area, screen_area);
}

void UIDrawer::fillArea(Area area, int r, int g, int b, int a) {
  SDL_Rect rect = {
      area.getX(), area.getY(), area.getWidth(), area.getHeight()
  };
  SDL_SetRenderDrawColor(window.getRenderer(), r, g, b, a);
  SDL_RenderFillRect(window.getRenderer(), &rect);
}

void UIDrawer::fillAreaWithBorder(Area area, int r, int g, int b, int a) {
  SDL_Rect rect = {
      area.getX() - 1, area.getY() - 1, area.getWidth() - 1, area.getHeight() - 1
  };
  SDL_Rect border = {
      area.getX(), area.getY(), area.getWidth(), area.getHeight()
  };

  SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 0);
  SDL_RenderFillRect(window.getRenderer(), &border);
  SDL_SetRenderDrawColor(window.getRenderer(), r, g, b, a);
  SDL_RenderFillRect(window.getRenderer(), &rect);
}

void UIDrawer::renderDeadMode() {
  Area upper_area(0, 0, width, ui_height);
  window.drawRectangle(upper_area, 0, 0, 0, 0);
  Area lower_area(0, starting_point, width, ui_height);
  window.drawRectangle(lower_area, 0, 0, 0, 0);
}
