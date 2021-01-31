//
// Created by andy on 26/11/20.
//

#ifndef TP_WOLFENSTEIN_SDLWINDOW_H
#define TP_WOLFENSTEIN_SDLWINDOW_H

#include <SDL_render.h>
#include <SDL_ttf.h>
#include <map>

#include "area.h"
#include "sdl_texture.h"
#include "client/map_info.h"
#include "client/sdl_exception.h"
#include "client/drawable.h"
#include "client/game/client_player.h"
#include "client/window_drawer.h"


class SdlWindow {
private:
    int width;
    int height;
    double width_prop;
    double height_prop;
    SDL_Window* window;
    SDL_Renderer* renderer;
    WindowDrawer window_drawer;
public:
    SdlWindow(int width, int height);
    ~SdlWindow();
    void fill();
    void fill(int r, int g, int b, int alpha);
    void render();
    SDL_Renderer* getRenderer() const;
    SDL_Surface* getSurface() const;
    void putTextureAt(SDL_Texture* texture, Area src, Area dest);
    void displayFullImage(SdlTexture& texture);
    void fillArea(Area area, int r, int g, int b, int a);
    void restore();
    int getWidth();
    int getHeight();
    void drawRectangle(Area& area, int r, int g, int b, int a);
    void loadImage(SDL_Texture* texture, Area& image_area, Area& screen_area);
};


#endif //TP_WOLFENSTEIN_SDLWINDOW_H

