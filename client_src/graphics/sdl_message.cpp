//
// Created by andy on 16/2/21.
//

#include "client/graphics/sdl_message.h"
#include <client/graphics/area.h>

#define FONTS_PATH "../client_src/resources/fonts/"
/*
SdlMessage::SdlMessage(std::string _text,
                       std::string font_name,
                       SDL_Color _color,
                       int _font_size) :
        font(TTF_OpenFont((FONTS_PATH + font_name).c_str(), _font_size)),
        text(std::move(_text)) {
    color = _color;
    surface = TTF_RenderText_Solid(font, text.c_str(), color);
}
*/
SDL_Texture* SdlMessage::loadMessage(SDL_Renderer* renderer,
                                     Area& message_area) {
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(message, nullptr, nullptr, &area_width, &area_height);
    message_area.setWidth(area_width);
    message_area.setHeight(area_height);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    return message;
}

SDL_Texture* SdlMessage::loadMessage(SDL_Renderer* renderer,
                                     Area& message_area,
                                     Area& screen_area) {
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(message, nullptr, nullptr, &area_width, &area_height);
    message_area.setWidth(area_width);
    message_area.setHeight(area_height);
    fillScreenArea(screen_area);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    return message;
}

void SdlMessage::fillScreenArea(Area& screen_area) {
    int text_width;
    int text_height;
    TTF_SizeText(font, text.c_str(), &text_width, &text_height);
    screen_area.setX(screen_area.getX()+ (screen_area.getWidth()-text_width)/2);
    screen_area.setWidth(text_width);
    TTF_SizeText(font, text.c_str(), &text_width, &text_height);
}

SdlMessage::SdlMessage(MessageParameters &message_parameters) :
      font(TTF_OpenFont((FONTS_PATH + message_parameters.getFontName()).c_str(),
                message_parameters.getFontSize())),
      text(message_parameters.getText()) {
    color = message_parameters.getFontColor();
    surface = TTF_RenderText_Solid(font, text.c_str(), color);
}
