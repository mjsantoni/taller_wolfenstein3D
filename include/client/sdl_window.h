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
#include "drawing_info.h"
#include "object_drawer.h"
#include "sdl_exception.h"
#include "drawable.h"

#include "client_player.h"
#include "ui_drawer.h"


class SdlWindow {
private:
    int width;
    int height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    ObjectDrawer object_drawer;
    UIDrawer ui_drawer;
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
    void putWall(int ray_no, DrawingInfo& drawing_info);
    void putFloorAndCeiling(int ray_no, DrawingInfo& drawing_info);
    void put3DObject(double distance, double pl_ob_angle, double x_prop,
                     Drawable& object);
    void drawPlayersWeapon(int weapon_number);
    int getWidth();
    void drawPlayerUI(ClientPlayer& player);
    void setDistanceInfo(std::map<double, double> ray_information,
                         std::vector<double> angles_list);
};


#endif //TP_WOLFENSTEIN_SDLWINDOW_H

