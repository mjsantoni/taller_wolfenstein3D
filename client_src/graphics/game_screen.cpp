//
// Created by andy on 22/1/21.
//

#include "client/graphics/game_screen.h"

#define MAX_WEAPON_ANIMATION 3

GameScreen::GameScreen(int width,
                       int height,
                       ClientMap& _map,
                       ClientPlayer& _player,
                       bool& _player_alive) :
        window(width, height),
        texture_manager(window, object_info_provider),
        object_drawer(window, object_info_provider, wall_distance_info,
                      angles_list, _map, texture_manager),
        map(_map),
        ray_caster(window, _map, wall_distance_info, object_info_provider,
                   angles_list, texture_manager),
        ui_drawer(object_info_provider, window),
        weapon_drawer(window, object_info_provider, texture_manager),
        menus_drawer(window),
        player(_player),
        player_alive(_player_alive) {
    ray_caster.setDimensions(width, (int) (0.8 * height));
    object_drawer.setDimensions(width, (int) (0.8 * height));
    ui_drawer.setDimensions((int) (0.8 * height), (int) (0.2 * height), width);
    weapon_drawer.setDimensions((int) (0.8 * height), width);
    TTF_Init();
}

void GameScreen::displayDeadScreen() {
    menus_drawer.displayDeadScreen();
}

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

void
GameScreen::render(bool render_background_and_objects) {
    int x = player.getXPosition();
    int y = player.getYPosition();
    if (render_background_and_objects) {
        ray_caster.renderBackground(x, y, player.getDirection());
        object_drawer.loadObjects(x, y, player.getDirection());
    }
    if (player_alive) {
        weapon_drawer.drawPlayersWeapon(player.getEquippedWeapon(),
                                        player_weapon_animation);
        ui_drawer.drawPlayerUI(player);
    } else {
        ui_drawer.renderDeadMode();
    }
    window.render();
    wall_distance_info.clear();
    angles_list.clear();
    if (player_attacking) {
        player_weapon_animation++;
        //player_weapon_animation %= (MAX_WEAPON_ANIMATION+1); // SOLO PARA ASEGURARME DE QUE NO SE PASE (NO DEBERIA)
    }
    if (player_weapon_animation > MAX_WEAPON_ANIMATION) {
        player_attacking = false;
        player_weapon_animation = 0;
    }
}

void GameScreen::displayLoadingScreen(bool waiting_for_input) {
    menus_drawer.displayLoadingScreen(waiting_for_input);
}

void GameScreen::displayRespawningScreen() {
    menus_drawer.displayRespawningScreen();
}

void GameScreen::displayStatistics(std::vector<std::vector<int>> statistics) {
    menus_drawer.displayStatistics(statistics);
}

void GameScreen::displayVictoryScreen() {
    menus_drawer.displayVictoryScreen();
}

void GameScreen::displayNetworkConnectionErrorScreen(std::string message) {
    menus_drawer.displayNetworkConnectingErrorScreen();
}

void GameScreen::displayDefeatScreen() {
    menus_drawer.displayDefeatScreen();
}

void GameScreen::setPlayerAttacking() {
    player_attacking = true;
    player_weapon_animation++;
}

void GameScreen::displayTimeOverScreen() {
    menus_drawer.displayTimeOverScreen();
}
