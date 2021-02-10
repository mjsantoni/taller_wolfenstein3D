//
// Created by andy on 27/11/20.
//

#ifndef TP_WOLFENSTEIN_RAYCASTER_H
#define TP_WOLFENSTEIN_RAYCASTER_H

#include "client/game/client_map.h"
#include "area.h"
#include "ray_info.h"
#include "client/map_info.h"
#include "sdl_window.h"
#include "client/calculator.h"
#include "../../../client_src/graphics/drawing_assistant.h"

class RayCaster {
public:
    RayCaster(SdlWindow& window, ClientMap& map, std::map<double, double>&
          wall_distance_info,std::map<int, std::pair<int, int>>& _floor_info,
          ObjectInfoProvider& info_provider, std::vector<double>& _angles_list);
    void renderBackground(int x, int y, double alpha);
    void setDimensions(int width, int height);
private:
    SdlWindow window;
    ClientMap& map;
    DrawingAssistant drawing_assistant;
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
};


#endif //TP_WOLFENSTEIN_RAYCASTER_H
