//
// Created by andy on 27/11/20.
//

#ifndef TP_WOLFENSTEIN_RAYCASTER_H
#define TP_WOLFENSTEIN_RAYCASTER_H

#include "client_map.h"
#include "area.h"
#include "client_wall.h"
#include "ray_info.h"
#include "map_info.h"
#include "sdl_window.h"
#include "calculator.h"

class RayCaster {
public:
    RayCaster(SdlWindow& window, ClientMap& map, std::map<double, double>&
          wall_distance_info,std::map<int, std::pair<int, int>>& _floor_info,
          ObjectInfoProvider& info_provider, std::vector<double>& _angles_list);
    void renderBackground(int x, int y, double alpha);
private:
    SdlWindow window;
    ClientMap& map;
    int window_width;
    int window_height;
    int width_prop;
    int height_prop;
    int map_grid_size;
    ObjectInfoProvider& info_provider;
    std::map<double, double>& wall_distance_info;
    std::vector<double>& angles_list;
    std::map<int, std::pair<int, int>>& floor_info;
    double ray_angle_delta = (double)60/320*2*M_PI/360;

    void castProjectionLine(int x, int y, double alpha, double beta,
                            ObjectInfo& drawing_info);
    void castProjectionLine_vertical(int x, int y, double alpha, double beta,
                                     ObjectInfo& drawing_info);
    void castProjectionLine_vertical_up(int x, int y, double alpha,
                                        double beta, ObjectInfo& drawing_info);
    void castProjectionLine_vertical_down(int x, int y, double alpha,
                                          double beta, ObjectInfo& drawing_info);
    void castProjectionLine_horizontal(int x, int y, double alpha, double beta,
                                       ObjectInfo& drawing_info);
    void castProjectionLine_horizontal_right(int x, int y, double alpha,
                                             double beta, ObjectInfo& drawing_info);
    void castProjectionLine_horizontal_left(int x, int y, double alpha,
                                            double beta, ObjectInfo& drawing_info);
    bool outOfBounds(ClientMap& map, int x_pos, bool is_vertical);
    void fillRayInfo(double beta, int x_pos, int y_pos, int delta_x,
                     int delta_y, ObjectInfo& object_info, int x_factor,
                     int y_factor);
    ObjectInfo fillObjectInfo(ObjectInfo& map_info);
    int calculateBorderFactor(bool should_decrease, int position);
    void saveRayInformation(double ray_angle, double distance);
    void drawCeiling(int x_pos, int y_pos);
    void drawFloor(int x_pos, int wall_posY, int wall_height);
    void setDimensions(int width, int height);
};


#endif //TP_WOLFENSTEIN_RAYCASTER_H
