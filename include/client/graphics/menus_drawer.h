//
// Created by andy on 31/1/21.
//

#ifndef TP_WOLFENSTEIN_MENUS_DRAWER_H
#define TP_WOLFENSTEIN_MENUS_DRAWER_H

#include "sdl_window.h"
#include <client/graphics/message_parameters.h>
#include <client/graphics/sdl_message.h>
#include <client/graphics/sdl_texture.h>

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
    void renderMessage(const std::string &message_text, Area &msg_area,
                               Area &screen_area,
                               MessageParameters message_parameters);
    void displayVictoryScreen();
    void renderMessage(const std::string &message_text, Area &msg_area,
                       Area &screen_area);
    void displayStatisticsHeaders();
    void displayTopKillers(std::vector<int> top_killers,
                           std::vector<int> top_killers_stats);
    void displayTopShooters(std::vector<int> top_shooters,
                            std::vector<int> top_shooters_stats);
    void displayTopScorers(std::vector<int> top_scorers,
                           std::vector<int> top_scorers_stats);
    void displayDefeatScreen();
    void displayNetworkConnectingErrorScreen();

    void displayTimeOverScreen();

    void displayEmptyStatisticsScreen();
};


#endif //TP_WOLFENSTEIN_MENUS_DRAWER_H
