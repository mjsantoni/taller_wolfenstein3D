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

class ObjectDrawingAssistant {
private:
    SdlWindow& window;
    std::map<double, double>& wall_distance_info;
    std::map<int, std::pair<int, int>>& floor_info;
    std::vector<double>& angles_list;
    int window_width;
    int window_height;
    int width_factor;
    int height_factor;
    int map_grid_size;
public:
    ObjectDrawingAssistant(SdlWindow &_window,
                           std::map<double, double> &_wall_distance_info,
                           std::map<int, std::pair<int, int>> &_floor_info,
                           std::vector<double> &_angles_list,
                           int _map_grid_size);
    SDL_Texture *getObjectImage(ObjectInfo &o_i, Area &image_area);
    void put3DObject(ObjectInfo &object_info, double pl_ob_angle);
    int findRayNumberForAngle(double beta);
    Area assembleScreenArea(ObjectInfo &object_info, double pl_ob_angle);
    int findObjectHeight(double distance, int object_height);
    int findObjectWidth(double distance, int object_width);
    double findWallDistanceForAngle(double angle);
    int findYPosForObject(int ray_no, double pl_ob_angle, double distance,
                          int object_height);
    int findXPosForObject(double pl_ob_beta, int object_width);
    Area findObjectProportions(ObjectInfo &object_info, double pl_ob_angle);

    void setDimensions(int width, int height);
};


#endif //TP_WOLFENSTEIN_OBJECT_DRAWING_ASSISTANT_H
