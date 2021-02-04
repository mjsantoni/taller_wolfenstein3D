//
// Created by andy on 22/1/21.
//

#ifndef TP_WOLFENSTEIN_GAME_SCREEN_H
#define TP_WOLFENSTEIN_GAME_SCREEN_H


#include "image_parser.h"
#include "client/object_info_provider.h"
#include "sdl_window.h"
#include "ray_caster.h"
#include "object_handler.h"
#include "ui_drawer.h"
#include "menus_drawer.h"

class GameScreen {
private:
    SdlWindow window;
    ObjectHandler object_handler;
    RayCaster ray_caster;
    UIDrawer ui_drawer;
    MenusDrawer menus_drawer;
    ClientMap& map;
    std::map<double, double> wall_distance_info;
    std::vector<double> angles_list;
    std::map<int, std::pair<int, int>> floor_info;
public:
    GameScreen(int width, int height, ObjectInfoProvider& object_info_provider,
               ClientMap& _map);
    void render(int x, int y, ClientPlayer& player);
    void renderDeadScreen();
    void renderRespawnScreen();
    void close();
    void displayIntro();
    void displayMatchModeMenu();
    void displayLevelSelectionMenu();

    std::vector<Area> getKeyScreenAreas();
};


#endif //TP_WOLFENSTEIN_GAME_SCREEN_H
