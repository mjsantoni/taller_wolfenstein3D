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
#include "object_drawing_assistant.h"

class ObjectDrawer {
private:
    SDL_Renderer* renderer;
    SdlWindow& window;
    ObjectInfoProvider& object_info_provider;
    int map_grid_size = 64;
    std::map<double, double>& wall_distance_info;
    std::map<int, std::pair<int, int>>& floor_info;
    std::vector<double>& angles_list;
    ClientMap& map;
    int safe_distance = 30;
    int sprite_counter = 0;
    ObjectDrawingAssistant drawing_assistant;
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
    double getGammaAngle(double player_angle, double object_angle);
    bool blockedByWall(double angle, double distance);
public:
    ObjectDrawer(SdlWindow& _window, ObjectInfoProvider& object_info_provider,
                 std::map<double, double>& wall_distance_info,
                 std::map<int, std::pair<int, int>>& _floor_info,
                 std::vector<double>& angles_list, ClientMap& map);
    void loadObjects(int x, int y, double player_angle);
    void setDimensions(int width, int height);
    int getObjectWidth(Drawable &drawable);
};


#endif //TP_WOLFENSTEIN_OBJECTDRAWER_H