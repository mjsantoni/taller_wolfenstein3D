//
// Created by andy on 22/1/21.
//

#ifndef TP_WOLFENSTEIN_GAME_SCREEN_H
#define TP_WOLFENSTEIN_GAME_SCREEN_H

#include "image_parser.h"
#include "client/object_info_provider.h"
#include "sdl_window.h"
#include "ray_caster.h"
#include "object_drawer.h"
#include "ui_drawer.h"
#include "menus_drawer.h"
#include "weapon_drawer.h"
#include "texture_manager.h"
#include <client/graphics/sdl_texture.h>

class GameScreen {
 private:
  SdlWindow window;
  ObjectInfoProvider object_info_provider;
  TextureManager texture_manager;
  ObjectDrawer object_drawer;
  RayCaster ray_caster;
  UIDrawer ui_drawer;
  WeaponDrawer weapon_drawer;
  MenusDrawer menus_drawer;
  ClientMap& map;
  ClientPlayer& player;
  std::map<double, double> wall_distance_info;
  std::vector<double> angles_list;
  bool& player_alive;
  int player_weapon_animation = 0;
  bool player_attacking = false;
  int max_animation_turns = 0;
 public:
  GameScreen(int width, int height, ClientMap& _map, ClientPlayer& _player,
             bool& _player_alive);
  ~GameScreen();
  void render(bool render_background_and_objects);
  void displayDeadScreen();
  void displayRespawningScreen();
  std::vector<Area> getKeyScreenAreas();
  void displayLoadingScreen(bool waiting_for_input);
  void displayStatistics(std::vector<std::vector<int>> statistics);
  void displayVictoryScreen();
  void displayNetworkConnectionErrorScreen();
  void displayDefeatScreen();
  void displayTimeOverScreen();
  void setPlayerAttacking(int weapon_no);
};

#endif //TP_WOLFENSTEIN_GAME_SCREEN_H
