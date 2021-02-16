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
    std::map<int, std::pair<int, int>> floor_info;
    bool& player_alive;
public:
    GameScreen(int width, int height, ClientMap& _map, ClientPlayer& _player,
               bool& _player_alive);
    void render();
    void render(std::vector<int> boolean_vector);
    void displayDeadScreen();
    void renderRespawnScreen();
    void close();
    void displayIntro();
    void displayMatchModeMenu();
    void displayLevelSelectionMenu();
    std::vector<Area> getKeyScreenAreas();
    void displayPlayerAttacking();
    void displayLoadingScreen(bool waiting_for_input);
    void displayRespawningScreen();
    void clearWindow();
    void displayStatistics(std::vector<int> statistics);
    void displayVictoryScreen();
};


#endif //TP_WOLFENSTEIN_GAME_SCREEN_H
