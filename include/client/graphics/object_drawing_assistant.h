//
// Created by andy on 10/2/21.
//

#ifndef TP_WOLFENSTEIN_OBJECT_DRAWING_ASSISTANT_H
#define TP_WOLFENSTEIN_OBJECT_DRAWING_ASSISTANT_H


#include <SDL_render.h>
#include <client/graphics/sdl_sprite.h>
#include <client/graphics/sdl_texture.h>
#include <client/object_info.h>
#include <client/graphics/area.h>
#include <map>
#include <client/graphics/sdl_window.h>

#define OBJECT_HEIGHT 600
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define VIEW_DIST 600
#define FOV 60

class ObjectDrawingAssistant {
private:
    SdlWindow& window;
    int window_width;
    int window_height;
    int width_factor;
    int height_factor;
    int map_grid_size = 64;
    int proj_plane_distance = (int) (((double) SCREEN_WIDTH/2) / tan(FOV/2));
public:
    explicit ObjectDrawingAssistant(SdlWindow &_window);
    SDL_Texture *getObjectImage(ObjectInfo &o_i, Area &image_area);
    void put3DObject(ObjectInfo &object_info, double pl_ob_angle);
    Area assembleScreenArea(ObjectInfo &object_info, double pl_ob_angle);
    Area findObjectProportions(ObjectInfo &object_info, double pl_ob_angle);
    void setDimensions(int width, int height);
    double findObjectHeight(double distance);
    int findY0(double object_height);
};


#endif //TP_WOLFENSTEIN_OBJECT_DRAWING_ASSISTANT_H
