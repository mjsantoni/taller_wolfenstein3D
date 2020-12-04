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
        //printf("Se lanza el rayo %d, con el angulo %f\n", i, angle);
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
    DrawingInfo drawing_info{};
    castProjectionLine_vertical(x, y, alpha, beta, drawing_info);
    //printf("Distancia vertical encontrada: %f\n", drawing_info.hit_distance);
    castProjectionLine_horizontal(x, y, alpha, beta, drawing_info);
    //printf("Distancia horizontal encontrada: %f\n", drawing_infow.hit_distance);
    //printf("Para el rayo %d se devuelve la distancia: %f\n",col, drawing_info.hit_distance);
    renderColumn(col, drawing_info);
}

void RayCaster::castProjectionLine_vertical(int x,
                                              int y,
                                              double alpha,
                                              double beta,
                                              DrawingInfo& drawing_info) {
    if (alpha <= M_PI)
        return castProjectionLine_vertical_up(x, y, alpha, beta, drawing_info);
    return castProjectionLine_vertical_down(x, y, alpha, beta, drawing_info);
}

void RayCaster::castProjectionLine_horizontal(int x,
                                                int y,
                                                double alpha,
                                                double beta,
                                                DrawingInfo& drawing_info) {
    if (alpha >= M_PI/2 && alpha <= 3*M_PI/2)
        return castProjectionLine_horizontal_left(x, y, alpha, beta,
                                                  drawing_info);
    return castProjectionLine_horizontal_right(x, y, alpha, beta, drawing_info);
}

void RayCaster::castProjectionLine_vertical_up(int x,
                                                 int y,
                                                 double alpha,
                                                 double beta,
                                                 DrawingInfo& drawing_info) {
    int delta_y = y%map.getGridSize();
    double delta_alpha = (alpha > M_PI/2) ? M_PI - alpha : alpha;
    bool ray_pointing_left = alpha >= M_PI/2;
    int x_inverter = (ray_pointing_left) ? -1 : 1;
    while (true) {
        int delta_x = calculateDelta(delta_y, delta_alpha) * x_inverter;
        if (outOfBounds(map, y-delta_y, true))
            return;

        int x_factor_h = ray_pointing_left ? -1 : 0;
        int x_factor = ((x+delta_x)%64 == 0) ? x_factor_h : 0;
        if (map.wallAtGrid(x+delta_x, y-delta_y, x_factor, -1, x, y)) {
            //printf("Se encontro una pared en la celda: (%d, %d) con un rayo vertical hacia arriba",
                   //grid_coordinates.first, grid_coordinates.second);
            fillRayInfo(beta, x, y, delta_x, -delta_y, drawing_info, 1);
            return;
        }
        delta_y += map.getGridSize();
    }
}

void RayCaster::castProjectionLine_vertical_down(int x,
                                                   int y,
                                                   double alpha,
                                                   double beta,
                                                   DrawingInfo& drawing_info) {
    int delta_y = map.getGridSize()-y%map.getGridSize();
    double delta_alpha = (alpha <= 3*M_PI/2) ? alpha - M_PI : 2*M_PI - alpha;
    bool ray_pointing_right = alpha <= 3*M_PI/2;
    int x_inverter = (ray_pointing_right) ? -1 : 1;
    while (true) {
        int delta_x = calculateDelta(delta_y, delta_alpha) * x_inverter;
        if (outOfBounds(map, y+delta_y, true))
            return;

        int x_factor_h = ray_pointing_right ? -1 : 0;
        int x_factor = ((x+delta_x)%64 == 0) ? x_factor_h : 0;
        if (map.wallAtGrid(x+delta_x, y+delta_y, x_factor, 0, x, y)) {
            //printf("Se encontro una pared en la celda: (%d, %d) con un rayo vertical hacia abajo",
                   //grid_coordinates.first, grid_coordinates.second);
            fillRayInfo(beta, x, y, delta_x, delta_y, drawing_info, 1);
            return;
        }
        delta_y += map.getGridSize();
    }
}

void RayCaster::castProjectionLine_horizontal_left(int x,
                                                     int y,
                                                     double alpha,
                                                     double beta,
                                                     DrawingInfo& drawing_info) {
    int delta_x = x%map.getGridSize();
    double delta_alpha = (alpha <= M_PI) ? alpha - M_PI/2 : 3*M_PI/2 - alpha;
    bool ray_pointing_up = alpha <= M_PI;
    int y_inverter = (ray_pointing_up) ? -1 : 1;

    while (true) {
        int delta_y = calculateDelta(delta_x, delta_alpha) * y_inverter;
        if (outOfBounds(map, x-delta_x, false))
            return;

        int y_factor_v = ray_pointing_up ? -1 : 0;
        int y_factor = ((y+delta_y)%64 == 0) ? y_factor_v : 0;
        if (map.wallAtGrid(x-delta_x, y+delta_y, -1, y_factor, x, y)) {
            //printf("Se encontro una pared en la celda: (%d, %d) con un rayo horizontal hacia la izquierda",
                   //grid_coordinates.first, grid_coordinates.second);
            fillRayInfo((float) beta, x, y, -delta_x, delta_y, drawing_info, 2);
            return;
        }
        delta_x += map.getGridSize();
    }
}

void RayCaster::castProjectionLine_horizontal_right(int x,
                                                      int y,
                                                      double alpha,
                                                      double beta,
                                                    DrawingInfo& drawing_info) {
    int delta_x = map.getGridSize()-x%map.getGridSize();
    double delta_alpha = (alpha <= M_PI/2) ? M_PI/2-alpha : alpha-3*M_PI/2;
    bool ray_pointing_up = alpha <= M_PI;
    int y_inverter = (ray_pointing_up) ? -1 : 1;
    while (true) {
        int delta_y = calculateDelta(delta_x, delta_alpha) * y_inverter;
        if (outOfBounds(map, x+delta_x, false))
            return;

        int y_factor_v = ray_pointing_up ? -1 : 0;
        int y_factor = ((y+delta_y)%64 == 0) ? y_factor_v : 0;
        if (map.wallAtGrid(x+delta_x, y+delta_y, 0, y_factor, x, y)) {
            //printf("Se encontro una pared en la celda: (%d, %d) con un rayo horizontal hacia la derecha",
                   //grid_coordinates.first, grid_coordinates.second);
            fillRayInfo(beta, x, y, delta_x, delta_y, drawing_info, 2);
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
    //printf("val x: %d\n", delta_x);
    //printf("val y:%d\n", delta_y);
    return sqrt(pow(delta_x, 2)+pow(delta_y, 2));
}

void RayCaster::renderColumn(int ray_no, DrawingInfo drawing_info) {
    window.put3DColumn(ray_no, drawing_info);
}

void RayCaster::fillRayInfo(double beta,
                            int x_pos,
                            int y_pos,
                            int delta_x,
                            int delta_y,
                            DrawingInfo& drawing_info,
                            int object_type) {
    double final_distance = calculateDistanceToWall(delta_x, delta_y)*cos(beta);
    if (final_distance >= drawing_info.hit_distance
                                && drawing_info.hit_distance != 0)
        return;
    drawing_info.hit_distance = final_distance;
    drawing_info.hit_x = x_pos+delta_x;
    drawing_info.hit_y = y_pos+delta_y;
    drawing_info.object_type = object_type;
    drawing_info.hit_grid_pos = (drawing_info.hit_x%GRID_SIZE == 0) ?
            drawing_info.hit_y % GRID_SIZE : drawing_info.hit_x % GRID_SIZE;
}
