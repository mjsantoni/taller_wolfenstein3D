//
// Created by andy on 10/2/21.
//

#ifndef TP_WOLFENSTEIN_RAY_CASTING_ASSISTANT_H
#define TP_WOLFENSTEIN_RAY_CASTING_ASSISTANT_H

#include <SDL_render.h>
#include <client/object_info.h>
#include <client/graphics/area.h>
#include <client/graphics/sdl_texture.h>
#include <client/graphics/sdl_window.h>
#include <map>
#include "texture_manager.h"
#include "screen_drawing_values.h"


class RayCastingAssistant {
private:
    SdlWindow& window;
    std::map<int, std::pair<int, int>>& floor_info;
    TextureManager& texture_manager;
    int screen_width;
    int screen_height;
    int map_grid_size = 64;
    int proj_plane_distance =
            (int) (( (double) SCREEN_DRAWING_WIDTH/2) / tan(FOV/2));
public:
    RayCastingAssistant(SdlWindow &_window,
                        std::map<int, std::pair<int, int>> &_floor_info,
                        TextureManager& _texture_manager);
    void drawFloor(int x_pos, int wall_posY, int wall_height);
    void drawCeiling(int x_pos, int y_pos);
    double findWallHeight(double distance);
    int findColumnStartingPoint(int col_height);
    void putWall(int ray_no, ObjectInfo& object_info);
    SDL_Texture* loadWallTexture(ObjectInfo& object_info, Area& image_area);
    void setDimensions(int width, int height);
    Area assembleScreenArea(int ray_no, ObjectInfo &object_info);
    void putFloorAndCeiling(int ray_no, ObjectInfo &object_info);

    int findWallStartingPoint(double wall_height);
};


#endif //TP_WOLFENSTEIN_RAY_CASTING_ASSISTANT_H
