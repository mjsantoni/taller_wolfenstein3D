//
// Created by andy on 16/2/21.
//

#ifndef TP_WOLFENSTEIN_SDL_MESSAGE_H
#define TP_WOLFENSTEIN_SDL_MESSAGE_H


#include <SDL_ttf.h>
#include <string>
#include "area.h"
#include "message_parameters.h"
#include "sdl_window.h"
#include <client/graphics/area.h>
#include <client/graphics/sdl_window.h>
#include "client_routes.h"

class SdlMessage {
private:
    SDL_Surface* surface;
    TTF_Font* font;
    SDL_Color color;
    std::string text;
    int area_width;
    int area_height;
public:
    explicit SdlMessage(MessageParameters& message_parameters);
    ~SdlMessage();
    SDL_Texture *
    loadMessage(SDL_Renderer *renderer, Area &message_area, Area &screen_area);
    void fillScreenArea(Area &screen_area);
    void renderMessage(SdlWindow &window, Area &src, Area &dest);
};

#endif //TP_WOLFENSTEIN_SDL_MESSAGE_H
