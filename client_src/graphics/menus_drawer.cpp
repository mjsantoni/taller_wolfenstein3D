//
// Created by andy on 31/1/21.
//

#include <zconf.h>
#include "client/graphics/menus_drawer.h"

MenusDrawer::MenusDrawer(SdlWindow& _window) : window(_window) {
    window_width = window.getWidth();
    window_height = window.getHeight();
    match_mode_new_game_area = Area(window_width/8, window_height/8,
            window_width/6, window_height/8);
    match_mode_join_game_area = Area(6*window_width/8, window_height/8,
                                     window_width/6, window_height/8);
    level_selection_easy =
            Area(window_width/2 - window_width/4, 4 * window_height/10,
                                     window_width/2, window_height/10);
    level_selection_medium =
            Area(window_width/2-window_width/4,6*window_height/10,
                                window_width/2, window_height/10);
    level_selection_hard =
            Area(window_width/2-window_width/4, 8 * window_height/10,
                                window_width/2, window_height/10);
}

void MenusDrawer::displayIntro() {
    SdlTexture intro_tex("../client_src/resources/menus/intro.jpg");
    displayFullImage(intro_tex);
    std::string message_text = "PRESS ANY KEY TO CONTINUE";
    Area screen_area(3*window_width/8, 5*window_height/6, window_width/2,
                     window_height/10);
    Area msg_area;
    MessageParameters msg_parms(message_text, "POLOBM__.TTF", 35);
    SDL_Texture* message = createMessage(message_text, msg_area, screen_area,
                                         msg_parms);
    window.loadImage(message, msg_area, screen_area);
    window.render();
}

void MenusDrawer::displayFullImage(SdlTexture& texture) {
    Area src_area;
    SDL_Texture* image = texture.loadTexture(window.getRenderer(), src_area);
    Area dest_area(0, 0, window_width, window_height);
    window.loadImage(image, src_area, dest_area);
}

SDL_Texture * MenusDrawer::createMessage(const std::string &message_text,
                                      Area &msg_area,
                                      Area &screen_area,
                                      MessageParameters message_parameters) {
    SdlMessage message(message_parameters);
    SDL_Texture* message_texture;
    message_texture =
                message.loadMessage(window.getRenderer(), msg_area,screen_area);

    return message_texture;
}

SDL_Texture* MenusDrawer::createMessage(const std::string& message,
                                        Area& msg_area,
                                        Area& screen_area) {
    TTF_Font* font =
            TTF_OpenFont("../client_src/resources/fonts/Action_Force.ttf", 25);
    SDL_Color color = {255, 255, 255};
    SDL_Surface* message_surf = TTF_RenderText_Solid(font,message.c_str(),
                                                     color);
    SDL_Texture* message_text =
            SDL_CreateTextureFromSurface(window.getRenderer(), message_surf);
    int m_width;
    int m_height;
    SDL_QueryTexture(message_text, nullptr, nullptr, &m_width, &m_height);
    msg_area.setWidth(m_width);
    msg_area.setHeight(m_height);
    TTF_CloseFont(font);
    SDL_FreeSurface(message_surf);
    return message_text;
}

void MenusDrawer::fillTextArea(TTF_Font* font,
                            const std::string& message,
                            Area& screen_area) {
    int text_width;
    int text_height;
    TTF_SizeText(font, message.c_str(), &text_width, &text_height);
}

void MenusDrawer::displayMatchModeMenu() {
    SdlTexture menu_tex("../client_src/resources/menus/match_mode_menu.jpg");
    displayFullImage(menu_tex);
    std::string message_text_1 = "New Game";
    std::string message_text_2 = "Join Game";
    Area msg_area_1;
    Area msg_area_2;
    SDL_Texture* message_1 =
            createMessage(message_text_1, msg_area_1,match_mode_join_game_area);
    SDL_Texture* message_2 =
            createMessage(message_text_2, msg_area_2,match_mode_join_game_area);
    window.loadImage(message_1, msg_area_1, match_mode_new_game_area);
    window.loadImage(message_2, msg_area_2, match_mode_join_game_area);
    window.render();
}

std::vector<Area> MenusDrawer::getKeyAreas() {
    return std::vector<Area>{match_mode_new_game_area,
                             match_mode_join_game_area,
                             level_selection_easy,
                             level_selection_medium,
                             level_selection_hard
                             };
}

void MenusDrawer::displayLevelSelectionMenu() {
    Area screen_area(0, 0, window_width, window_height);
    window.drawRectangle(screen_area, 0, 0, 0, 0);
    std::string intro = "Choose your map";
    std::string level_1_text = "Map 1";
    std::string level_2_text = "Map 2";
    std::string level_3_text = "Map 3";
    Area intro_msg_area;
    Area screen_msg_area(window_width/2-window_width/4, window_height/10,
                         window_width/2, window_height/5);
    Area msg_area_1;
    Area msg_area_2;
    Area msg_area_3;
    SDL_Texture* intro_message =
            createMessage(intro, intro_msg_area, screen_msg_area);
    SDL_Texture* message_1 =
            createMessage(level_1_text, msg_area_1, level_selection_easy);
    SDL_Texture* message_2 =
            createMessage(level_2_text, msg_area_2, level_selection_medium);
    SDL_Texture* message_3 =
            createMessage(level_3_text, msg_area_3,level_selection_hard);
    window.loadImage(intro_message, intro_msg_area, screen_msg_area);
    window.loadImage(message_1, msg_area_1, level_selection_easy);
    window.loadImage(message_2, msg_area_2, level_selection_medium);
    window.loadImage(message_3, msg_area_3, level_selection_hard);
    window.render();
}

void MenusDrawer::displayLoadingScreen(bool waiting_for_input) {
    SdlTexture menu_tex("../client_src/resources/menus/loading_screen.png");
    displayFullImage(menu_tex);
    Area screen_area(5*window_width/8, 3*window_height/4, 5*window_width/16,
                     window_height/6);
    std::string message_text = "Press 'P' when ready";
    if (!waiting_for_input) {
        screen_area = Area(5*window_width/8, 3*window_height/4, window_width/4,
                                  window_height/6);
        message_text = "Loading...";
    }
    Area msg_area;
    MessageParameters msg_parms(message_text, "Snowstorm Kraft.ttf", 35);
    SDL_Texture* message =
            createMessage(message_text, msg_area, screen_area, msg_parms);
    window.loadImage(message, msg_area, screen_area);
    window.render();
}

void MenusDrawer::displayRespawningScreen() {
    Area screen_area(0, 0, window_width, window_height);
    window.drawRectangle(screen_area, 255, 0, 0, 0);
    std::string message_text = "DEAD! RESPAWNING";
    screen_area = Area(window_width/4, window_height/4, window_width/2,
                      window_height/4);
    Area msg_area;
    SDL_Texture* message =
            createMessage(message_text, msg_area, screen_area);
    window.loadImage(message, msg_area, screen_area);
    window.render();
}

void MenusDrawer::displayDeadScreen() {
    Area screen_area(0, 0, window_width, window_height);
    window.drawRectangle(screen_area, 0, 0, 0, 0);
    std::string message_text = "DEAD! NO COMING BACK THIS TIME";
    screen_area = Area(window_width/8, window_height/4, 3*window_width/4,
                       window_height/4);
    Area msg_area;
    SDL_Texture* message =
            createMessage(message_text, msg_area, screen_area);
    window.loadImage(message, msg_area, screen_area);
    window.render();
}

void MenusDrawer::displayStatistics(std::vector<std::vector<int>> statistics) {
    std::vector<int> top_killers = statistics[0];
    std::vector<int> top_shooters = statistics[1];
    std::vector<int> top_scorers = statistics[2];
    std::vector<int> top_killers_stats = statistics[3];
    std::vector<int> top_shooters_stats = statistics[4];
    std::vector<int> top_scorers_stats = statistics[5];
    Area screen_area(0, 0, window_width, window_height);
    window.drawRectangle(screen_area, 0, 0, 0, 0);
    std::string top_killer_header = "TOP KILLERS";
    std::string top_shooter_header = "TOP SHOOTERS";
    std::string top_scorer_header = "TOP SCORERS";
    Area header_area_1;
    Area header_area_2;
    Area header_area_3;
    SDL_Texture* message_1 =
            createMessage(top_killer_header, header_area_1, screen_area);
    SDL_Texture* message_2 =
            createMessage(top_shooter_header, header_area_2, screen_area);
    SDL_Texture* message_3 =
            createMessage(top_scorer_header, header_area_3, screen_area);
    Area screen_area_1 = Area(window_width/6, 0, window_width/8,
                       window_height/12);
    Area screen_area_2 = Area(3*window_width/6, 0,
                              window_width/8, window_height/12);
    Area screen_area_3 = Area(5*window_width/6, 0,
                              window_width/8, window_height/12);
    window.loadImage(message_1, header_area_1, screen_area_1);
    window.loadImage(message_2, header_area_2, screen_area_2);
    window.loadImage(message_3, header_area_3, screen_area_3);
    for (int i = 0 ; i < top_killers.size() ; ++i) {
        std::string msg_text_1 = "Player " + std::to_string(top_killers[i]) +
                ": " + std::to_string(top_killers_stats[i]);
        std::string msg_text_2 = "Player " + std::to_string(top_shooters[i]) +
                ": " + std::to_string(top_shooters_stats[i]);
        std::string msg_text_3 = "Player " + std::to_string(top_scorers[i]) +
                ": " + std::to_string(top_scorers_stats[i]);
        Area e_msg_area_1;
        Area e_msg_area_2;
        Area e_msg_area_3;
        Area e_screen_area_1 = Area(window_width/4, (2+2*i)*window_height/12,
                                  window_width/2, window_height/12);
        Area e_screen_area_2 = Area(window_width/4, (2+2*i)*window_height/12,
                                  window_width/2, window_height/12);
        Area e_screen_area_3 = Area(window_width/4, window_height/12, window_width/2,
                                  window_height/12);
        SDL_Texture* e_message_1 =
                createMessage(msg_text_1, e_msg_area_1, e_screen_area_1);
        SDL_Texture* e_message_2 =
                createMessage(msg_text_2, e_msg_area_2,e_screen_area_2);
        SDL_Texture* e_message_3 =
                createMessage(msg_text_3, e_msg_area_3, e_screen_area_3);
        window.loadImage(e_message_1, e_msg_area_1, e_screen_area_1);
        window.loadImage(e_message_2, e_msg_area_2, e_screen_area_2);
        window.loadImage(e_message_3, e_msg_area_3, e_screen_area_3);
    }
    window.render();
    sleep(10);
}

void MenusDrawer::displayVictoryScreen() {
    SdlTexture menu_tex("../client_src/resources/menus/victory_screen.jpg");
    displayFullImage(menu_tex);
    Area screen_area(3*window_width/8, 3*window_height/4, window_width/4,
                     window_height/6);
    std::string message_text = "VICTORY";
    MessageParameters msg_parms(message_text, "vikingsquadboldital.ttf", 75);
    Area msg_area;
    SDL_Texture* message =
            createMessage(message_text, msg_area, screen_area, msg_parms);
    window.loadImage(message, msg_area, screen_area);
    window.render();
}
