//
// Created by andy on 16/2/21.
//

#include "client/graphics/sdl_message.h"

SdlMessage::SdlMessage(MessageParameters& message_parameters) :
    font(TTF_OpenFont((CLIENT_FONTS_ROUTE +
                          message_parameters.getFontName()).c_str(),
                      message_parameters.getFontSize())),
    text(message_parameters.getText()) {
  color = message_parameters.getFontColor();
  surface = TTF_RenderText_Solid(font, text.c_str(), color);
}

SDL_Texture* SdlMessage::loadMessage(SDL_Renderer* renderer,
                                     Area& message_area,
                                     Area& screen_area) {
  SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_QueryTexture(message, nullptr, nullptr, &area_width, &area_height);
  message_area.setWidth(area_width);
  message_area.setHeight(area_height);
  fillScreenArea(screen_area);
  return message;
}

void SdlMessage::fillScreenArea(Area& screen_area) {
  int text_width;
  int text_height;
  TTF_SizeText(font, text.c_str(), &text_width, &text_height);
  screen_area.setX(screen_area.getX() + (screen_area.getWidth() - text_width) / 2);
  screen_area.setWidth(text_width);
  TTF_SizeText(font, text.c_str(), &text_width, &text_height);
}

void SdlMessage::renderMessage(SdlWindow& window,
                               Area& src,
                               Area& dest) {
  SDL_Renderer* renderer = window.getRenderer();
  SDL_Texture* texture = loadMessage(renderer, src, dest);
  SDL_Rect sdlSrc = {
      src.getX(), src.getY(), src.getWidth(), src.getHeight()
  };
  // donde se pega, y si hay diferencia de dimensiones
  SDL_Rect sdlDest = {
      dest.getX(), dest.getY(), dest.getWidth(), dest.getHeight()
  };
  SDL_RenderCopy(renderer, texture, &sdlSrc, &sdlDest);
}

SdlMessage::~SdlMessage() {
  SDL_FreeSurface(surface);
  TTF_CloseFont(font);
}
