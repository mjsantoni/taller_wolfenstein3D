//
// Created by andy on 31/1/21.
//

#ifndef TP_WOLFENSTEIN_MENUS_DRAWER_H
#define TP_WOLFENSTEIN_MENUS_DRAWER_H

#include "sdl_window.h"
#include <client/graphics/message_parameters.h>
#include <client/graphics/sdl_message.h>

class MenusDrawer {
private:
    SdlWindow& window;
    int window_width;
    int window_height;
    bool active = true;
    Area match_mode_new_game_area;
    Area match_mode_join_game_area;
    Area level_selection_easy;
    Area level_selection_medium;
    Area level_selection_hard;
public:
    explicit MenusDrawer(SdlWindow& _window);
    void displayIntro();
    SDL_Texture* createMessage(const std::string &message,
                               Area &msg_area,Area &screen_area);
    void fillTextArea(TTF_Font *font, const std::string &message,
                      Area &screen_area);
    void displayMatchModeMenu();
    void displayLevelSelectionMenu();
    void displayFullImage(SdlTexture &texture);
    std::vector<Area> getKeyAreas();
    void displayLoadingScreen(bool waiting_for_input);
    void displayRespawningScreen();
    void displayDeadScreen();
    void displayStatistics(std::vector<std::vector<int>> statistics);
    SDL_Texture *createMessage(const std::string &message_text, Area &msg_area,
                               Area &screen_area,
                               MessageParameters message_parameters);
    void displayVictoryScreen();
};


#endif //TP_WOLFENSTEIN_MENUS_DRAWER_H
