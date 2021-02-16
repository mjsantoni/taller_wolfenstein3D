//
// Created by andy on 16/2/21.
//

#ifndef TP_WOLFENSTEIN_SDL_MESSAGE_H
#define TP_WOLFENSTEIN_SDL_MESSAGE_H


#include <SDL_ttf.h>
#include <string>
#include "area.h"
#include "message_parameters.h"

class SdlMessage {
private:
    SDL_Surface* surface;
    TTF_Font* font;
    SDL_Color color;
    std::string text;
    int area_width;
    int area_height;
public:
    SdlMessage(std::string _text, std::string font_name, SDL_Color _color,
               int _font_size);
    explicit SdlMessage(MessageParameters& message_parameters);
    SDL_Texture *loadMessage(SDL_Renderer *renderer, Area &message_area);
    SDL_Texture *
    loadMessage(SDL_Renderer *renderer, Area &message_area, Area &screen_area);
    void fillScreenArea(Area &screen_area);
};

#endif //TP_WOLFENSTEIN_SDL_MESSAGE_H
