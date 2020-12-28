//
// Created by andy on 27/11/20.
//

#ifndef TP_WOLFENSTEIN_RAYCASTER_H
#define TP_WOLFENSTEIN_RAYCASTER_H

#include "client_map.h"
#include "area.h"
#include "client_wall.h"
#include "ray_info.h"
#include "drawing_info.h"

class RayCaster {
public:
    RayCaster(SdlWindow& window, ClientMap& map);
    void render3DScreen(int x, int y, double alpha);
    void loadObjects(int x, int y, double alpha);
private:
    SdlWindow window;
    ClientMap& map;
    std::map<double, double> ray_information;
    std::vector<double> angles_list;
    double ray_angle_delta = (double)60/320*2*M_PI/360;

    void castProjectionLine(int x,int y, double alpha, double beta,
                            DrawingInfo& drawing_info);
    void castProjectionLine_vertical(int x, int y, double alpha, double beta,
                                       DrawingInfo& drawing_info);
    void castProjectionLine_vertical_up(int x, int y, double alpha,
                                        double beta, DrawingInfo& drawing_info);
    void castProjectionLine_vertical_down(int x, int y, double alpha,
                                        double beta, DrawingInfo& drawing_info);
    void castProjectionLine_horizontal(int x, int y, double alpha, double beta,
                                         DrawingInfo& drawing_info);
    void castProjectionLine_horizontal_right(int x, int y, double alpha,
                                        double beta, DrawingInfo& drawing_info);
    void castProjectionLine_horizontal_left(int x, int y, double alpha,
                                        double beta, DrawingInfo& drawing_info);
    int calculateDelta(int delta_coord, double delta_alpha);
    bool outOfBounds(ClientMap& map, int x_pos, bool is_vertical);
    double calculateDistance(int delta_x, int delta_y);
    void fillDrawingInfo(double beta, int x_pos, int y_pos, int delta_x,
                         int delta_y, DrawingInfo& drawing_info, int x_factor,
                         int y_factor);
    int calculateBorderFactor(bool should_decrease, int position);
    bool shouldDraw(double player_angle, double object_angle);
    double getObjectAngle(int p_x, int p_y, std::pair<int, int> o_pos);
    double normalize(double alpha);
    void renderObject(int x_pos, int y_pos, double player_angle, double object_angle,
                      Drawable& object);
    void saveRayInformation(double ray_angle, double distance);
    void renderFloorAndCeiling(int x, int y, double alpha);
    void renderWalls(int x, int y, double alpha);
    bool blockedByWall(double angle, double distance);
};


#endif //TP_WOLFENSTEIN_RAYCASTER_H
