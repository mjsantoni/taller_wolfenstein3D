//
// Created by andy on 22/1/21.
//

#include "client/game_screen.h"

GameScreen::GameScreen(int width,
                       int height,
                       ObjectInfoProvider& object_info_provider,
                       ClientMap& _map) :
   window(width, height),
   object_handler(window, object_info_provider, wall_distance_info, floor_info,
                  angles_list, _map),
   map(_map),
   ray_caster(window, _map, wall_distance_info, floor_info,
                         object_info_provider, angles_list),
   ui_drawer(object_info_provider, window) {
    object_handler.setDimensions(width, (int) (0.8 * height));
    ui_drawer.setDimensions((int) (0.8 * height), (int) (0.2 * height), width);
}

void GameScreen::displayIntro() {
    SdlTexture intro_tex("../client_src/resources/intro.jpg");
    window.displayFullImage(intro_tex);
    window.render();
}

void GameScreen::render(int x, int y, ClientPlayer& player) {
    window.fill();
    ray_caster.renderBackground(x, y, player.getDirection());
    object_handler.loadObjects(x, y, player.getDirection());
    ui_drawer.drawPlayerUI(player);
    window.render();
    wall_distance_info.clear();
    angles_list.clear();
}

