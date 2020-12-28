//
// Created by andy on 26/11/20.
//

#ifndef TP_WOLFENSTEIN_SDLWINDOW_H
#define TP_WOLFENSTEIN_SDLWINDOW_H

#include <SDL_render.h>
#include <map>
#include "area.h"
#include "sdl_texture.h"
#include "drawing_info.h"
#include "object_drawer.h"
#include "sdl_exception.h"
#include "drawable.h"


class SdlWindow {
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
    void fillSquare(Area area);
    void restore();
    void putWall(int ray_no, DrawingInfo& drawing_info);
    void putFloorAndCeiling(int ray_no, DrawingInfo& drawing_info);
    void put3DObject(double distance, int dist_to_perimeter, double pl_ob_angle,
                     Drawable& object);
    int findColumnStartingPoint(int distance, int& col_height);
    int getWidth();
private:
    int width;
    int height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    ObjectDrawer drawer;

    Area assembleScreenArea(int ray_no, DrawingInfo& drawing_info);
    Area assembleScreenArea(DrawingInfo& drawing_info, double distance,
                            int dist_to_perimeter, double pl_ob_angle);
};


#endif //TP_WOLFENSTEIN_SDLWINDOW_H

