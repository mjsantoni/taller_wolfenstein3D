//
// Created by andy on 30/1/21.
//

#include "client/game/client_event_handler.h"
#

void ClientEventHandler::handleWeaponChange(int weapon_number) {
    Change change(CL_CHANGE_WEAPON, 0, 0, weapon_number);
    change_queue.push(change);

}

void ClientEventHandler::handleCameraTurn(int direction) {
    Change change(CL_UPDATE_DIRECTION, 0, 0, direction);
    change_queue.push(change);
    //player.updateDirection(direction);
}

ClientEventHandler::ClientEventHandler(ClientPlayer &_player,
                                       GameScreen& _screen,
                                       SharedQueue<Change>& _change_queue) :
                                       player(_player),
                                       screen(_screen),
                                       change_queue(_change_queue){
}

int ClientEventHandler::handleMatchModeScreenEvent(SDL_Event event) {
    if (event.type != SDL_MOUSEBUTTONDOWN)
        return 0;
    auto& mouse_button_event = (SDL_MouseButtonEvent&) event;
    int mouse_x_pos = mouse_button_event.x;
    int mouse_y_pos = mouse_button_event.y;
    if (eventInsideArea(match_mode_new_game_area, mouse_x_pos, mouse_y_pos))
        return 1;
    if (eventInsideArea(match_mode_join_game_area, mouse_x_pos, mouse_y_pos))
        return 2;
    return 0;
}

int ClientEventHandler::handleLevelSelectionEvent(SDL_Event event) {
    if (event.type != SDL_MOUSEBUTTONDOWN)
        return 0;
    auto& mouse_button_event = (SDL_MouseButtonEvent&) event;
    int mouse_x_pos = mouse_button_event.x;
    int mouse_y_pos = mouse_button_event.y;
    if (eventInsideArea(level_selection_easy, mouse_x_pos, mouse_y_pos))
        return 1;
    if (eventInsideArea(level_selection_medium, mouse_x_pos, mouse_y_pos))
        return 2;
    if (eventInsideArea(level_selection_hard, mouse_x_pos, mouse_y_pos))
        return 3;
    return 0;
}

void ClientEventHandler::defineKeyScreenAreas(std::vector<Area> key_areas) {
    match_mode_new_game_area = key_areas[0];
    match_mode_join_game_area = key_areas[1];
    level_selection_easy = key_areas[2];
    level_selection_medium = key_areas[3];
    level_selection_hard = key_areas[4];
}

bool ClientEventHandler::eventInsideArea(Area& area, int x_pos, int y_pos) {
    bool inside_x =
            x_pos >= area.getX() && x_pos <= area.getX() + area.getWidth();
    bool inside_y =
            y_pos >= area.getY() && y_pos <= area.getY() + area.getHeight();
    return inside_x && inside_y;
}

void ClientEventHandler::handlePlayerShooting() {
    Change change(CL_PLAYER_SHOOTING, 0, 0, 0);
    change_queue.push(change);
}

int ClientEventHandler::handleLoadingScreenEvent(SDL_Event event) {
    if (event.type != SDL_KEYDOWN)
        return 0;
    auto& key_event = (SDL_KeyboardEvent&) event;
    if (key_event.keysym.sym == SDLK_p)
        return 1;
    return 0;
}