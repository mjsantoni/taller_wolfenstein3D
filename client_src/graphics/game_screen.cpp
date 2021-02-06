//
// Created by andy on 22/1/21.
//

#include "client/graphics/game_screen.h"

GameScreen::GameScreen(int width,
                       int height,
                       ObjectInfoProvider& object_info_provider,
                       ClientMap& _map) :
        window(width, height),
        object_drawer(window, object_info_provider, wall_distance_info, floor_info,
                      angles_list, _map),
        map(_map),
        ray_caster(window, _map, wall_distance_info, floor_info,
                         object_info_provider, angles_list),
        ui_drawer(object_info_provider, window),
        menus_drawer(window) {
    ray_caster.setDimensions(width, (int) (0.8 * height));
    object_drawer.setDimensions(width, (int) (0.8 * height));
    ui_drawer.setDimensions((int) (0.8 * height), (int) (0.2 * height), width);
    TTF_Init();
}

void GameScreen::render(int x, int y, ClientPlayer& player) {
    window.fill();
    ray_caster.renderBackground(x, y, player.getDirection());
    object_drawer.loadObjects(x, y, player.getDirection());
    ui_drawer.drawPlayerUI(player);
    window.render();
    wall_distance_info.clear();
    angles_list.clear();
    close();
}

void GameScreen::renderDeadScreen() {}

void GameScreen::renderRespawnScreen() {}

void GameScreen::close() {
    TTF_Quit();
}

void GameScreen::displayIntro() {
    menus_drawer.displayIntro();
}

void GameScreen::displayMatchModeMenu() {
    menus_drawer.displayMatchModeMenu();
}

std::vector<Area> GameScreen::getKeyScreenAreas() {
    return menus_drawer.getKeyAreas();
}

void GameScreen::displayLevelSelectionMenu() {
    return menus_drawer.displayLevelSelectionMenu();
}


