//
// Created by andy on 3/1/21.
//

#include <SDL_ttf.h>
#include "client/ui_drawer.h"

UIDrawer::UIDrawer() : player_face("../client_src/resources/ui/player_face.png",
                                  184, 124, 4, 2, 0, 0) {}

void UIDrawer::initialize(SDL_Renderer *_renderer,
                   int _starting_point,
                   int _height,
                   int _width) {
    renderer = _renderer;
    starting_point = _starting_point;
    height = _height;
    width = _width;
}

void UIDrawer::drawPlayerUI(ClientPlayer& player) {
    TTF_Init();
    Area ui_rect_area(0, starting_point, width, height);
    fillArea(ui_rect_area, 3, 69, 64, 0);
    drawPlayersLevel(player.getLevel());
    drawPlayersScore(player.getScore());
    drawPlayersLives(player.getLives());
    drawPlayersImage();
    drawPlayersHealth(player.getHealth());
    drawPlayersAmmo(player.getAmmo());
    /*
    drawPlayersGun();
     */
    TTF_Quit();
    box_starting_point = 0;
}

void UIDrawer::drawPlayersLevel(int players_level) {
    drawBox("Level", players_level);
}

void UIDrawer::drawPlayersScore(int players_score) {
    drawBox("Score", players_score);
}

void UIDrawer::drawPlayersLives(int players_lives) {
    drawBox("Lives", players_lives);
}

void UIDrawer::drawPlayersHealth(int players_health) {
    drawBox("Health", players_health);
}

void UIDrawer::drawPlayersAmmo(int players_ammo) {
    drawBox("Ammo", players_ammo);
}

void UIDrawer::drawPlayersImage() {
    box_starting_point += h_padding;
    Area rect_area(box_starting_point, starting_point + 10,
                   width/10, height - 20);
    fillArea(rect_area, 8, 2, 175, 0);
    Area screen_area(box_starting_point, starting_point + 15, width/10,
                     height - 30);
    Area img_area;

    SDL_Texture* player_image = player_face.loadTexture(renderer, img_area, 0);

    putTextureAt(player_image, img_area, screen_area);
    box_starting_point += width / 10;
}

void UIDrawer::drawBox(const std::string& message, int value) {
    box_starting_point += h_padding;
    Area rect_area(box_starting_point, starting_point + 10,
                   width/10, height - 20);
    fillArea(rect_area, 8, 2, 175, 0);
    Area msg_area;
    Area header_screen_area(box_starting_point, starting_point + 15,
                            width/10, height / 2 - 10);
    SDL_Texture* head_message = createMessage(message, msg_area,
                                              header_screen_area, false);

    putTextureAt(head_message, msg_area, header_screen_area);
    Area sub_screen_area(box_starting_point, starting_point + 15 +
                                             height / 2 - 10, width / 10, height / 2 - 10);
    SDL_Texture* sub_message = createMessage(std::to_string(value),
                                             msg_area, sub_screen_area, true);

    putTextureAt(sub_message, msg_area, sub_screen_area);
    SDL_DestroyTexture(head_message);
    SDL_DestroyTexture(sub_message);
    box_starting_point += width / 10;
}

SDL_Texture* UIDrawer::createMessage(const std::string& message,
                                      Area& msg_area,
                                      Area& screen_area,
                                      bool fill_text_area) {
    TTF_Font* font = TTF_OpenFont("../client_src/resources/fonts/AnkeHand.ttf"
            ,25);
    SDL_Color color = {255, 255, 255};
    SDL_Surface* message_surf = TTF_RenderText_Solid(font,message.c_str(),
                                                     color);
    SDL_Texture* message_text = SDL_CreateTextureFromSurface(renderer,
                                                             message_surf);
    int m_width;
    int m_height;
    SDL_QueryTexture(message_text, nullptr, nullptr, &m_width, &m_height);
    msg_area.setWidth(m_width);
    msg_area.setHeight(m_height);
    if (fill_text_area)
        fillTextArea(font, message, screen_area);

    TTF_CloseFont(font);
    SDL_FreeSurface(message_surf);
    return message_text;
}

void UIDrawer::fillArea(Area area, int r, int g, int b, int a) {
    SDL_Rect rect = {
            area.getX(), area.getY(), area.getWidth(), area.getHeight()
    };
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &rect);
}

void UIDrawer::fillTextArea(TTF_Font* font,
                             const std::string& message,
                             Area& screen_area) {
    int text_width;
    int text_height;
    TTF_SizeText(font, message.c_str(), &text_width, &text_height);
    screen_area.setX(screen_area.getX()+ (screen_area.getWidth()-text_width)/2);
    screen_area.setWidth(text_width);
}

void UIDrawer::putTextureAt(SDL_Texture* texture, Area src, Area dest) {
    SDL_Rect sdlSrc = {
            src.getX(), src.getY(), src.getWidth(), src.getHeight()
    };
    // donde se pega, y si hay diferencia de dimensiones
    SDL_Rect sdlDest = {
            dest.getX(), dest.getY(), dest.getWidth(), dest.getHeight()
    };
    SDL_RenderCopy(renderer, texture, &sdlSrc, &sdlDest);
}


