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


class DrawingAssistant {
private:
    SdlWindow& window;
    std::map<int, std::pair<int, int>>& floor_info;
    int window_width;
    int window_height;
    int width_factor;
    int height_factor;
    int map_grid_size;

public:
    DrawingAssistant(SdlWindow &_window,
                     std::map<int, std::pair<int, int>> &_floor_info,
                     int _map_grid_size);
    void drawFloor(int x_pos, int wall_posY, int wall_height);
    void drawCeiling(int x_pos, int y_pos);
    int findColumnHeight(int distance);
    int findColumnStartingPoint(int col_height);
    void putWall(int ray_no, ObjectInfo& object_info);
    SDL_Texture* loadWallTexture(ObjectInfo& object_info, Area& image_area);
    void setDimensions(int width, int height);
    Area assembleScreenArea(int ray_no, ObjectInfo &object_info);
    void putFloorAndCeiling(int ray_no, ObjectInfo &object_info);
};


#endif //TP_WOLFENSTEIN_DRAWING_ASSISTANT_H
