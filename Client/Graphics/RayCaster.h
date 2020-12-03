//
// Created by andy on 27/11/20.
//

#ifndef TP_WOLFENSTEIN_RAYCASTER_H
#define TP_WOLFENSTEIN_RAYCASTER_H

#include "../Game/Map.h"
#include "Area.h"
#include "../Game/Wall_3d.h"
#include "RayInfo.h"
#include "DrawingInfo.h"

class RayCaster {
public:
    RayCaster(SdlWindow& window, Map& map);
    void render3DScreen(int x, int y, double alpha);
private:
    SdlWindow window;
    Map& map;

    void castProjectionLine(int col, int x,int y, double alpha, double beta);
    void castProjectionLine_vertical(int x, int y, double alpha, double beta,
                                       RayInfo& ray_info);
    void castProjectionLine_vertical_up(int x, int y, double alpha,
                                        double beta, RayInfo& ray_info);
    void castProjectionLine_vertical_down(int x, int y, double alpha,
                                        double beta, RayInfo& ray_info);
    void castProjectionLine_horizontal(int x, int y, double alpha, double beta,
                                         RayInfo& ray_info);
    void castProjectionLine_horizontal_right(int x, int y, double alpha,
                                        double beta, RayInfo& ray_info);
    void castProjectionLine_horizontal_left(int x, int y, double alpha,
                                        double beta, RayInfo& ray_info);
    int calculateDelta(int delta_coord, double delta_alpha);
    bool outOfBounds(Map& map, int x_pos, bool is_vertical);
    double calculateDistanceToWall(int delta_x, int delta_y);
    void renderColumn(int ray_no, DrawingInfo drawing_info);
    void fillRayInfo_h(double beta, int x_pos, int y_pos, int delta_x,
                       int delta_y, RayInfo& ray_info, int object_type);
    void fillRayInfo_v(double beta, int x_pos, int y_pos, int delta_x,
                       int delta_y, RayInfo& ray_info, int object_type);
    void getObjectInfo(RayInfo& ray_info, DrawingInfo& drawing_info);
    void fillRayInfo_default(RayInfo& ray_info, bool is_vertical);
};


#endif //TP_WOLFENSTEIN_RAYCASTER_H
