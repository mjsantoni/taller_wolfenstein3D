//
// Created by andy on 10/2/21.
//

#ifndef TP_WOLFENSTEIN_DRAWING_ASSISTANT_H
#define TP_WOLFENSTEIN_DRAWING_ASSISTANT_H

#include <SDL_render.h>
#include <client/object_info.h>
#include <client/graphics/area.h>
#include <client/graphics/sdl_texture.h>
#include <client/graphics/sdl_window.h>
#include <map>

#define SCREEN_HEIGHT 700
#define SCREEN_WIDTH 700
#define FOV 60
#define WALL_HEIGHT 700


class DrawingAssistant {
private:
    SdlWindow& window;
    std::map<int, std::pair<int, int>>& floor_info;
    int window_width;
    int window_height;
    double width_factor;
    double height_factor;
    int map_grid_size = 64;
    int proj_plane_distance = (int) (( (double) SCREEN_WIDTH/2) / tan(FOV/2));
public:
    DrawingAssistant(SdlWindow &_window,
                     std::map<int, std::pair<int, int>> &_floor_info);
    void drawFloor(int x_pos, int wall_posY, int wall_height);
    void drawCeiling(int x_pos, int y_pos);
    double findWallHeight(int distance);
    int findColumnStartingPoint(int col_height);
    void putWall(int ray_no, ObjectInfo& object_info);
    SDL_Texture* loadWallTexture(ObjectInfo& object_info, Area& image_area);
    void setDimensions(int width, int height);
    Area assembleScreenArea(int ray_no, ObjectInfo &object_info);
    void putFloorAndCeiling(int ray_no, ObjectInfo &object_info);

    int findY0(int wall_height);
};


#endif //TP_WOLFENSTEIN_DRAWING_ASSISTANT_H
