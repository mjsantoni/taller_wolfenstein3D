//
// Created by andy on 4/12/20.
//

#ifndef TP_WOLFENSTEIN_OBJECTDRAWER_H
#define TP_WOLFENSTEIN_OBJECTDRAWER_H

#include "sdl_window.h"
#include <vector>
#include <map>
#include <limits>
#include "image_parser.h"
#include "image_info.h"
#include "client/calculator.h"
#include "client/game/client_map.h"

class ObjectDrawer {
private:
    SDL_Renderer* renderer;
    SdlWindow& window;
    ObjectInfoProvider& object_info_provider;
    int window_width;
    int window_height;
    int width_prop;
    int height_prop;
    int map_grid_size;
    std::map<double, double>& wall_distance_info;
    std::map<int, std::pair<int, int>>& floor_info;
    std::vector<double>& angles_list;
    ClientMap& map;
    int safe_distance = 30;
    int sprite_counter = 0;
    bool shouldDraw(double player_angle, double os_angle, double of_angle,
                    double& diff_angle);
    bool shouldDraw_borderCase(double os_angle, double of_angle,
                               double fov_starting_angle,
                               double fov_finishing_angle, double& diff_angle);
    double getObjectAngle(int p_x, int p_y, std::pair<int, int> o_pos);
    std::pair<int, int> projectObjectOnMap(Drawable& object,
                                           double player_angle);
    double calculateObjectStartingXPos(double os_angle, double of_angle,
                                       double diff_angle);
    void renderObject(int x_pos, int y_pos, double player_angle,
                      double object_angle, double x_prop, Drawable& object);
    double findWallDistanceForAngle(double angle);
    double getGammaAngle(double player_angle, double object_angle);
    bool blockedByWall(double angle, double distance);
    void put3DObject(ObjectInfo& object_info, double pl_ob_angle);
public:
    ObjectDrawer(SdlWindow& _window, ObjectInfoProvider& object_info_provider,
                 std::map<double, double>& wall_distance_info,
                 std::map<int, std::pair<int, int>>& _floor_info,
                 std::vector<double>& angles_list, ClientMap& map);
    Area findObjectProportions(ObjectInfo& object_info, double pl_ob_angle);
    int findXPosForObject(double pl_ob_beta, int object_width);
    int findYPosForObject(int ray_no, double pl_ob_angle, double distance,
                          int object_height);
    int findObjectHeight(double distance, int object_height);
    int findObjectWidth(double distance, int object_width);
    int findRayNumberForAngle(double beta);

    Area assembleScreenArea(ObjectInfo& object_info, double pl_ob_angle);
    void loadObjects(int x, int y, double player_angle);
    void setDimensions(int width, int height);
    SDL_Texture *getObjectImage(ObjectInfo &o_i, Area &image_area);
};


#endif //TP_WOLFENSTEIN_OBJECTDRAWER_H