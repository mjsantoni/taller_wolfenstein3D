//
// Created by andy on 30/1/21.
//

#ifndef TP_WOLFENSTEIN_CLIENT_EVENT_HANDLER_H
#define TP_WOLFENSTEIN_CLIENT_EVENT_HANDLER_H

#include <common/events.h>
#include <common/change.h>
#include "client_player.h"
#include "client/graphics/game_screen.h"
#include <common/shared_queue.h>

class ClientEventHandler {
private:
    ClientPlayer& player;
    GameScreen& screen;
    SharedQueue<Change>& change_queue;
    Area match_mode_new_game_area;
    Area match_mode_join_game_area;
    Area level_selection_easy;
    Area level_selection_medium;
    Area level_selection_hard;
public:
    ClientEventHandler(ClientPlayer& _player, GameScreen& _screen,
                       SharedQueue<Change>& _change_queue);
    void handleWeaponChange(int weapon_number);
    void handleCameraTurn(int direction);
    int handleMatchModeScreenEvent(SDL_Event event);
    int handleLevelSelectionEvent(SDL_Event event);
    void defineKeyScreenAreas(std::vector<Area> key_areas);
    bool eventInsideArea(Area &area, int x_pos, int y_pos);
    void handlePlayerShooting();
};



#endif //TP_WOLFENSTEIN_CLIENT_EVENT_HANDLER_H
