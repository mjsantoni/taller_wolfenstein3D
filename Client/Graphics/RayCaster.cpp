//
// Created by andy on 27/11/20.
//

#include "RayCaster.h"
#include <cmath>
#include <thread>

#define PROJECTION_PLANE_WIDTH 320
#define PROJECTION_PLANE_HEIGHT 200
#define FOV_ANGLE 60
#define GRID_SIZE 64

RayCaster::RayCaster(SdlWindow& window, Map& map) : window(window), map(map) {}

void RayCaster::render3DScreen(int x, int y, double alpha) {
    double angle = alpha + 0.523599;
    //printf("Ingresa el jugador en pos (%d, %d), con angulo %f\n", x, y, alpha);
    //printf("Se inicia el recorrido en: %f\n", angle);
    std::pair<int, int> grid = map.calculateGrid(x, y);
    for (int i = 0; i < PROJECTION_PLANE_WIDTH; ++i) {
        //printf("Con el jugador en (%d, %d), ", grid.first, grid.second);
        //printf("se lanza el rayo %d, con el angulo %f\n", i, angle);
        castProjectionLine(i, x, y, angle, angle - alpha);
        angle -= 0.0032724;
        if (angle < 0) {
            angle += 2*M_PI;
            alpha += 2*M_PI;
        }
    }
    //printf("Se finaliza el recorrido en: %f\n", angle);
    window.render();
}

void RayCaster::castProjectionLine(int col,
                                   int x,
                                   int y,
                                   double alpha,
                                   double beta) {
    int obj_v;
    int obj_h;
    RayInfo ray_info;
    DrawingInfo drawing_info{};
    castProjectionLine_vertical(x, y, alpha, beta, ray_info);
    castProjectionLine_horizontal(x, y, alpha, beta, ray_info);
    //printf("Distancia vertical encontrada: %f\n", ray_info.vertical_distance);
    //printf("Distancia horizontal encontrada: %f\n", ray_info.horizontal_distance);

    getObjectInfo(ray_info, drawing_info);
    //printf("Para el angulo %f se devuelve la distancia: %f\n",alpha, drawing_info.hit_distance);
    renderColumn(col, drawing_info);
}

void RayCaster::castProjectionLine_vertical(int x,
                                              int y,
                                              double alpha,
                                              double beta,
                                              RayInfo& ray_info) {
    if (alpha <= M_PI)
        return castProjectionLine_vertical_up(x, y, alpha, beta, ray_info);
    return castProjectionLine_vertical_down(x, y, alpha, beta, ray_info);
}

void RayCaster::castProjectionLine_horizontal(int x,
                                                int y,
                                                double alpha,
                                                double beta,
                                                RayInfo& ray_info) {
    if (alpha >= M_PI/2 && alpha <= 3*M_PI/2)
        return castProjectionLine_horizontal_left(x, y, alpha, beta, ray_info);
    return castProjectionLine_horizontal_right(x, y, alpha, beta, ray_info);
}

void RayCaster::castProjectionLine_vertical_up(int x,
                                                 int y,
                                                 double alpha,
                                                 double beta,
                                                 RayInfo& ray_info) {
    int delta_y = y%map.getGridSize();
    double delta_alpha = (alpha > M_PI/2) ? M_PI - alpha : alpha;
    while (true) {
        int delta_x = calculateDelta(delta_y, delta_alpha);
        if (alpha >= M_PI/2)
            delta_x *= -1;
        if (outOfBounds(map, y-delta_y, true)) {
            fillRayInfo_default(ray_info, true);
            return;
        }
        std::pair<int, int> grid_coordinates =
                map.calculateGrid(x+delta_x, y-delta_y, 0, -1);
        if (map.wallAtGrid(grid_coordinates)) {
            //printf("Se encontro una pared en la celda: (%d, %d) con un rayo vertical hacia arriba",
                   //grid_coordinates.first, grid_coordinates.second);
            fillRayInfo_v(beta, x, y, delta_x, -delta_y, ray_info, 1);
            return;
        }
        delta_y += map.getGridSize();
    }
}

void RayCaster::castProjectionLine_vertical_down(int x,
                                                   int y,
                                                   double alpha,
                                                   double beta,
                                                   RayInfo& ray_info) {
    int delta_y = map.getGridSize()-y%map.getGridSize();
    double delta_alpha = (alpha <= 3*M_PI/2) ? alpha - M_PI : 2*M_PI - alpha;
    while (true) {
        int delta_x = calculateDelta(delta_y, delta_alpha);
        if (alpha <= 3*M_PI/2)
            delta_x *= -1;
        if (outOfBounds(map, y+delta_y, true)) {
            fillRayInfo_default(ray_info, true);
            return;
        }
        std::pair<int, int> grid_coordinates =
                map.calculateGrid(x+delta_x, y+delta_y, 0, 0);
        if (map.wallAtGrid(grid_coordinates)) {
            //printf("Se encontro una pared en la celda: (%d, %d) con un rayo vertical hacia abajo",
                   //grid_coordinates.first, grid_coordinates.second);
            fillRayInfo_v(beta, x, y, delta_x, delta_y, ray_info, 1);
            return;
        }
        delta_y += map.getGridSize();
    }
}

void RayCaster::castProjectionLine_horizontal_left(int x,
                                                     int y,
                                                     double alpha,
                                                     double beta,
                                                     RayInfo& ray_info) {
    int delta_x = x%map.getGridSize();
    double delta_alpha = (alpha <= M_PI) ? alpha - M_PI/2 : 3*M_PI/2 - alpha;
    while (true) {
        int delta_y = calculateDelta(delta_x, delta_alpha);
        if (alpha <= M_PI)
            delta_y *= -1;
        if (outOfBounds(map, x-delta_x, false)) {
            fillRayInfo_default(ray_info, false);
            return;
        }
        std::pair<int, int> grid_coordinates =
                map.calculateGrid(x-delta_x, y+delta_y, -1, 0);
        if (map.wallAtGrid(grid_coordinates)) {
            //printf("Se encontro una pared en la celda: (%d, %d) con un rayo horizontal hacia la izquierda",
                   //grid_coordinates.first, grid_coordinates.second);
            fillRayInfo_h(beta, x, y, -delta_x, delta_y, ray_info, 2);
            return;
        }
        delta_x += map.getGridSize();
    }
}

void RayCaster::castProjectionLine_horizontal_right(int x,
                                                      int y,
                                                      double alpha,
                                                      double beta,
                                                    RayInfo& ray_info) {
    int delta_x = map.getGridSize()-x%map.getGridSize();
    double delta_alpha = (alpha <= M_PI/2) ? M_PI/2-alpha : alpha-3*M_PI/2;
    while (true) {
        int delta_y = calculateDelta(delta_x, delta_alpha);
        if (alpha <= M_PI)
            delta_y *= -1;
        if (outOfBounds(map, x+delta_x, false)) {
            fillRayInfo_default(ray_info, false);
            return;
        }
        std::pair<int, int> grid_coordinates =
                map.calculateGrid(x+delta_x, y+delta_y, 0, 0);
        if (map.wallAtGrid(grid_coordinates)) {
            //printf("Se encontro una pared en la celda: (%d, %d) con un rayo horizontal hacia la derecha",
                   //grid_coordinates.first, grid_coordinates.second);
            fillRayInfo_h(beta, x, y, delta_x, delta_y, ray_info, 2);
            return;
        }
        delta_x += map.getGridSize();
    }
}

int RayCaster::calculateDelta(int delta_coord, double delta_alpha) {
    return (int) (delta_coord/tan(delta_alpha));
}

bool RayCaster::outOfBounds(Map& map, int pos, bool is_vertical) {
    if (is_vertical)
        return map.outOfVerticalBounds(pos);
    return map.outOfHorizontalBounds(pos);
}

double RayCaster::calculateDistanceToWall(int delta_x, int delta_y) {
    return sqrt(pow(delta_x, 2)+pow(delta_y, 2));
}

void RayCaster::renderColumn(int ray_no, DrawingInfo drawing_info) {
    window.put3DColumn(ray_no, drawing_info);
}


void RayCaster::fillRayInfo_v(double beta,
                              int x_pos,
                              int y_pos,
                              int delta_x,
                              int delta_y,
                              RayInfo& ray_info,
                              int object_type){
    double final_distance = calculateDistanceToWall(delta_x, delta_y)*cos(beta);
    //printf(" a una distancia de %f\n", final_distance);
    ray_info.vertical_distance = final_distance;
    ray_info.vertical_hit_x = x_pos+delta_x;
    ray_info.vertical_hit_y = y_pos+delta_y;
    ray_info.horizontal_grid_pos = x_pos%GRID_SIZE;
    ray_info.vertical_object_type = object_type;
}

void RayCaster::fillRayInfo_h(double beta,
                              int x_pos,
                              int y_pos,
                              int delta_x,
                              int delta_y,
                              RayInfo& ray_info,
                              int object_type){
    double final_distance = calculateDistanceToWall(delta_x, delta_y)*cos(beta);
    //printf(" a una distancia de %f\n", final_distance);
    ray_info.horizontal_distance = final_distance;
    ray_info.horizontal_hit_x = x_pos+delta_x;
    ray_info.horizontal_hit_y = y_pos+delta_y;
    ray_info.horizontal_object_type = object_type;
    ray_info.vertical_grid_pos = y_pos%GRID_SIZE;
}

void RayCaster::fillRayInfo_default(RayInfo& ray_info, bool is_vertical) {
    if (is_vertical)
        ray_info.vertical_distance = std::numeric_limits<int>::max();
    else
        ray_info.horizontal_distance = std::numeric_limits<int>::max();
}

void RayCaster::getObjectInfo(RayInfo &ray_info, DrawingInfo &drawing_info) {
    double dist = (ray_info.vertical_distance < ray_info.horizontal_distance) ?
            ray_info.vertical_distance : ray_info.horizontal_distance;
    int object = (ray_info.vertical_distance < ray_info.horizontal_distance) ?
            ray_info.vertical_object_type : ray_info.horizontal_object_type;
    int grid_pos = (ray_info.vertical_distance < ray_info.horizontal_distance) ?
            ray_info.horizontal_grid_pos : ray_info.vertical_grid_pos;
    int hit_x = (ray_info.vertical_distance < ray_info.horizontal_distance) ?
                ray_info.vertical_hit_x: ray_info.horizontal_hit_x;
    int hit_y = (ray_info.vertical_distance < ray_info.horizontal_distance) ?
                ray_info.vertical_hit_y: ray_info.horizontal_hit_y;
    drawing_info.object_type = object;
    drawing_info.hit_distance = dist;
    drawing_info.hit_x = hit_x;
    drawing_info.hit_y = hit_y;
    drawing_info.object_x_pos = grid_pos;
}
