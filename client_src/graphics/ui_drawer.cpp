//
// Created by andy on 3/1/21.
//

#include <SDL_ttf.h>
#include "client/graphics/ui_drawer.h"

UIDrawer::UIDrawer(ObjectInfoProvider& _info_provider, SdlWindow& _window) :
                       player_face("../client_src/resources/ui/player_face.png",
                       184, 124, 4, 2, 0, 0), info_provider(_info_provider),
                       window(_window) {}

void UIDrawer::setDimensions(int _starting_point,
                             int _ui_height,
                             int _width) {
    starting_point = _starting_point;
    ui_height = _ui_height;
    window_height = starting_point + _ui_height;
    width = _width;
}

void UIDrawer::drawPlayerUI(ClientPlayer& player) {
    drawPlayersEquippedWeapon(player.getEquippedWeapon());
    TTF_Init();
    Area ui_rect_area(0, starting_point, width, ui_height);
    fillArea(ui_rect_area, 3, 69, 64, 0);
    drawPlayersLevel(player.getLevel());
    drawPlayersScore(player.getScore());
    drawPlayersLives(player.getLives());
    drawPlayersImage();
    drawPlayersHealth(player.getHealth());
    drawPlayersAmmo(player.getAmmo());
    drawPlayersWeaponIcon(player.getEquippedWeapon());
    /*

     */
    TTF_Quit();
    box_starting_point = 0;
    text_starting_point = 0;
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
    text_starting_point += h_padding;
    Area rect_area(box_starting_point, starting_point + 10,
                   width/10, ui_height - 20);
    fillAreaWithBorder(rect_area, 8, 2, 175, 0);
    Area screen_area(text_starting_point, starting_point + 15,
                     width/10 - 2*h_padding, ui_height - 30);
    Area img_area;
    SDL_Texture* player_image = player_face.loadTexture(window.getRenderer(), img_area, 0);
    putTextureAt(player_image, img_area, screen_area);
    box_starting_point += width / 10;
    text_starting_point += width / 10 - h_padding;
}

void UIDrawer::drawPlayersWeaponIcon(int players_weapon) {
    box_starting_point += 2 * h_padding;
    Area rect_area(box_starting_point, starting_point + 10,
                   width/5, ui_height - 20);
    fillAreaWithBorder(rect_area, 8, 2, 175, 0);
    ObjectInfo object_info = info_provider.getObjectInfo(players_weapon
            + WEAPON_ICON_DELTA);
    SdlTexture weapon_icon(object_info.getImagePath());
    Area image_area;
    SDL_Texture* weapon_texture = weapon_icon.loadTexture(window.getRenderer(), image_area);
    Area screen_area(text_starting_point,starting_point+15, width/5-2*h_padding,
                     ui_height - 30);
    putTextureAt(weapon_texture, image_area, screen_area);
}

void UIDrawer::drawBox(const std::string& message, int value) {
    text_starting_point += h_padding;
    Area rect_area(box_starting_point, starting_point + 10,
                   width/10, ui_height - 20);
    fillAreaWithBorder(rect_area, 8, 2, 175, 0);
    Area msg_area;
    Area header_screen_area(text_starting_point, starting_point + 15,
                            width/10 - 2*h_padding, ui_height / 2 - 10);
    SDL_Texture* head_message = createMessage(message, msg_area,
                                              header_screen_area, false);

    putTextureAt(head_message, msg_area, header_screen_area);
    Area sub_screen_area(text_starting_point, starting_point + 15 +
                                              ui_height / 2 - 10, width / 10 - 2 * h_padding, ui_height / 2 - 10);
    SDL_Texture* sub_message = createMessage(std::to_string(value),
                                             msg_area, sub_screen_area, true);

    putTextureAt(sub_message, msg_area, sub_screen_area);
    SDL_DestroyTexture(head_message);
    SDL_DestroyTexture(sub_message);
    box_starting_point += width / 10;
    text_starting_point += width / 10 - h_padding;
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
    SDL_Texture* message_text =
            SDL_CreateTextureFromSurface(window.getRenderer(), message_surf);
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
    SDL_SetRenderDrawColor(window.getRenderer(), r, g, b, a);
    SDL_RenderFillRect(window.getRenderer(), &rect);
}

void UIDrawer::fillAreaWithBorder(Area area, int r, int g, int b, int a) {
    SDL_Rect rect = {
            area.getX()-1, area.getY()-1, area.getWidth()-1, area.getHeight()-1
    };
    SDL_Rect border = {
            area.getX(), area.getY(), area.getWidth(), area.getHeight()
    };

    SDL_SetRenderDrawColor(window.getRenderer(), 0, 0, 0, 0);
    SDL_RenderFillRect(window.getRenderer(), &border);
    SDL_SetRenderDrawColor(window.getRenderer(), r, g, b, a);
    SDL_RenderFillRect(window.getRenderer(), &rect);
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
    SDL_RenderCopy(window.getRenderer(), texture, &sdlSrc, &sdlDest);
}

void UIDrawer::drawPlayersEquippedWeapon(int weapon_number) {
    ObjectInfo object_info = info_provider.getObjectInfo(weapon_number
            + EQ_WEAPON_DELTA);
    Area image_area;
    SDL_Texture* texture = getWeaponSprite(object_info, image_area);
    Area screen_area = assembleScreenWeaponArea(object_info);
    window.loadImage(texture, image_area, screen_area);
    SDL_DestroyTexture(texture);
}

SDL_Texture* UIDrawer::getWeaponSprite(ObjectInfo& o_i, Area& image_area) {
    SdlSprite sdl_sprite(o_i.getImagePath(), o_i.getImageWidth(),
                         o_i.getImageHeight(), o_i.getSpriteCols(),
                         o_i.getSpriteRows(), o_i.getSpriteHPadding(),
                         o_i.getSpriteVPadding());
    SDL_Texture* image = sdl_sprite.loadTexture(window.getRenderer(), image_area,
                                                o_i.getSpriteAnimationNo());
    return image;
}

Area UIDrawer::assembleScreenWeaponArea(ObjectInfo& object_info) {
    int weapon_window_width = (int) (object_info.getObjectWidth() * width);
    int weapon_window_height = (int) (object_info.getObjectHeight()
            * window_height);
    int starting_y_pos = starting_point - weapon_window_height;
    int starting_x_pos = (width - weapon_window_width) / 2;
    Area screen_area(starting_x_pos, starting_y_pos, weapon_window_width,
                     weapon_window_height);
    return screen_area;
}

void UIDrawer::displayPlayerShooting(int weapon_number) {
    ObjectInfo object_info = info_provider.getObjectInfo(weapon_number
                                                         + EQ_WEAPON_DELTA);
    object_info.setSpriteAnimationNo(2);
    Area image_area;
    SDL_Texture* texture = getWeaponSprite(object_info, image_area);
    Area screen_area = assembleScreenWeaponArea(object_info);
    window.loadImage(texture, image_area, screen_area);
    SDL_DestroyTexture(texture);
    window.render();
}

void UIDrawer::displayPlayerStopShooting(int weapon_number) {
    ObjectInfo object_info = info_provider.getObjectInfo(weapon_number
                                                         + EQ_WEAPON_DELTA);
    object_info.setSpriteAnimationNo(0);
    Area image_area;
    SDL_Texture* texture = getWeaponSprite(object_info, image_area);
    Area screen_area = assembleScreenWeaponArea(object_info);
    window.loadImage(texture, image_area, screen_area);
    window.render();
}
