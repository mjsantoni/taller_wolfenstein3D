//
// Created by andy on 31/1/21.
//

#include "client/graphics/menus_drawer.h"

MenusDrawer::MenusDrawer(SdlWindow& _window) : window(_window) {
    window_width = window.getWidth();
    window_height = window.getHeight();
    match_mode_new_game_area = Area(window_width/8, window_height/8,
            window_width/6, window_height/8);
    match_mode_join_game_area = Area(window_width/8, window_height/8,
                                     window_width/6, window_height/8);
}

void MenusDrawer::displayIntro() {
    SdlTexture intro_tex("../client_src/resources/menus/intro.jpg");
    displayFullImage(intro_tex);
    std::string message_text = "Press any key to continue";
    Area screen_area(window_width/3, 2*window_height/3, window_width/2,
                     window_height/10);
    Area msg_area;
    SDL_Texture* message = createMessage(message_text, msg_area, screen_area);
    window.loadImage(message, msg_area, screen_area);
    window.render();
}

void MenusDrawer::displayFullImage(SdlTexture& texture) {
    Area src_area;
    texture.loadTexture(window.getRenderer(), src_area);
    Area dest_area(0, 0, window_width, window_height);
    window.loadImage(texture.getTexture(), src_area, dest_area);
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
    Area screen_area_1(window_width/8, window_height/8,
                       window_width/6, window_height/8);
    Area screen_area_2(6*window_width/8 , window_height/8,
                       window_width/6, window_height/8);
    displayFullImage(menu_tex);
    std::string message_text_1 = "New Game";
    std::string message_text_2 = "Join Game";
    Area msg_area_1;
    Area msg_area_2;
    SDL_Texture* message_1 =
            createMessage(message_text_1, msg_area_1, screen_area_1);
    SDL_Texture* message_2 =
            createMessage(message_text_2, msg_area_2, screen_area_2);
    window.loadImage(message_1, msg_area_1, screen_area_1);
    window.loadImage(message_2, msg_area_2, screen_area_2);
    window.render();
}

std::vector<Area> MenusDrawer::getKeyAreas() {
    return std::vector<Area>{match_mode_new_game_area,match_mode_new_game_area};
}