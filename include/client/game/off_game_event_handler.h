//
// Created by andy on 9/2/21.
//

#ifndef TP_WOLFENSTEIN_OFF_GAME_EVENT_HANDLER_H
#define TP_WOLFENSTEIN_OFF_GAME_EVENT_HANDLER_H

#include <SDL_events.h>
#include <client/graphics/area.h>
#include <vector>

class OffGameEventHandler {
private:
    Area match_mode_new_game_area;
    Area match_mode_join_game_area;
    Area level_selection_easy;
    Area level_selection_medium;
    Area level_selection_hard;
public:
    int handleLoadingScreenEvent(SDL_Event event);
    int handleMatchModeScreenEvent(SDL_Event event);
    int handleLevelSelectionEvent(SDL_Event event);
    void defineKeyScreenAreas(std::vector<Area> key_areas);
    bool eventInsideArea(Area &area, int x_pos, int y_pos);

};


#endif //TP_WOLFENSTEIN_OFF_GAME_EVENT_HANDLER_H
