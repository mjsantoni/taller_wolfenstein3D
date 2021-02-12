//
// Created by andy on 27/11/20.
//

#include "client/graphics/ray_caster.h"

#include <thread>

#define PROJECTION_PLANE_WIDTH 700
#define PROJECTION_PLANE_HEIGHT 700
#define FOV_ANGLE 60
#define GRID_SIZE 64

RayCaster::RayCaster(SdlWindow& window,
                     ClientMap& map,
                     std::map<double, double>& _wall_distance_info,
                     std::map<int, std::pair<int, int>>& _floor_info,
                     ObjectInfoProvider& _info_provider,
                     std::vector<double>& _angles_list) :
            window(window), wall_distance_info(_wall_distance_info), map(map),
            info_provider(_info_provider), floor_info(_floor_info),
            angles_list(_angles_list),
            drawing_assistant(window, _floor_info){
}

void RayCaster::renderBackground(int x, int y, double alpha) {
    double angle = Calculator::normalize(alpha + 0.523599);
    for (int ray = 0; ray < PROJECTION_PLANE_WIDTH; ++ray) {
        //printf("Con el jugador en (%d, %d), ", grid.first, grid.second);
        printf("Se lanza el rayo %d, con el angulo %f\n", ray, angle);
        ObjectInfo object_info{};
        double beta = Calculator::calculateBeta(angle, alpha);
        castProjectionLine(x, y, angle, beta, object_info);
        object_info = fillObjectInfo(object_info);
        printf("Para el angulo %f se devuelve la distancia: %f\n",beta, object_info.getHitDistance());
        object_info.setHitDistance(object_info.getHitDistance()*cos(beta));
        drawing_assistant.putFloorAndCeiling(ray, object_info);
        drawing_assistant.putWall(ray, object_info);
        angle -= ray_angle_delta;
        if (angle < 0) {
            angle += 2*M_PI;
            alpha += 2*M_PI;
        }
    }
}

ObjectInfo RayCaster::fillObjectInfo(ObjectInfo& map_info) {
    ObjectInfo object_info =
            info_provider.getObjectInfo(map_info.getObjectType());
    object_info.setHitDistance(map_info.getHitDistance());
    object_info.setHitGridPos(map_info.getHitGridPos());
    return object_info;
}

void RayCaster::castProjectionLine(int x,
                                   int y,
                                   double alpha,
                                   double beta,
                                   ObjectInfo& object_info) {
    castProjectionLine_vertical(x, y, alpha, beta, object_info);
    //printf("Distancia vertical encontrada: %f\n", object_info.hit_distance);
    castProjectionLine_horizontal(x, y, alpha, beta, object_info);
    //printf("Distancia horizontal encontrada: %f\n", object_info.hit_distance);
    saveRayInformation(beta, object_info.getHitDistance());
}

void RayCaster::castProjectionLine_vertical(int x,
                                            int y,
                                            double alpha,
                                            double beta,
                                            ObjectInfo& object_info) {
    if (alpha <= M_PI)
        return castProjectionLine_vertical_up(x, y, alpha, beta, object_info);
    return castProjectionLine_vertical_down(x, y, alpha, beta, object_info);
}

void RayCaster::castProjectionLine_horizontal(int x,
                                              int y,
                                              double alpha,
                                              double beta,
                                              ObjectInfo& object_info) {
    if (alpha >= M_PI/2 && alpha <= 3*M_PI/2)
        return castProjectionLine_horizontal_left(x, y, alpha, beta,
                                                  object_info);
    return castProjectionLine_horizontal_right(x, y, alpha, beta, object_info);
}

void RayCaster::castProjectionLine_vertical_up(int x,
                                               int y,
                                               double alpha,
                                               double beta,
                                               ObjectInfo& object_info) {
    int delta_y = y % map.getGridSize();
    double lambda = (alpha > M_PI/2) ? M_PI - alpha : alpha;
    bool ray_pointing_left = alpha >= M_PI/2;
    int x_inverter = (ray_pointing_left) ? -1 : 1;
    while (true) {
        int delta_x = Calculator::calculateDelta(delta_y, lambda) * x_inverter;
        if (outOfBounds(map, y-delta_y, true))
            return;

        int x_factor = calculateBorderFactor(ray_pointing_left, x+delta_x);
        if (map.wallAtGrid(x+delta_x, y-delta_y, x_factor, -1)) {
            //printf("Se encontro una pared en la celda: (%d, %d) con un rayo vertical hacia arriba",
                   //grid_coordinates.first, grid_coordinates.second);
            fillRayInfo(beta, x, y, delta_x, -delta_y, object_info,
                        x_factor,
                        -1);
            return;
        }
        delta_y += map.getGridSize();
    }
}

void RayCaster::castProjectionLine_vertical_down(int x,
                                                 int y,
                                                 double alpha,
                                                 double beta,
                                                 ObjectInfo& object_info) {
    int delta_y = map.getGridSize()-y%map.getGridSize();
    double lambda = (alpha <= 3*M_PI/2) ? alpha - M_PI : 2*M_PI - alpha;
    bool ray_pointing_right = alpha <= 3*M_PI/2;
    int x_inverter = (ray_pointing_right) ? -1 : 1;
    while (true) {
        int delta_x = Calculator::calculateDelta(delta_y, lambda) * x_inverter;
        if (outOfBounds(map, y+delta_y, true))
            return;

        int x_factor = calculateBorderFactor(ray_pointing_right, x+delta_x);
        if (map.wallAtGrid(x+delta_x, y+delta_y, x_factor, 0)) {
            //printf("Se encontro una pared en la celda: (%d, %d) con un rayo vertical hacia abajo",
                   //grid_coordinates.first, grid_coordinates.second);
            fillRayInfo(beta, x, y, delta_x, delta_y, object_info,
                        x_factor, 0);
            return;
        }
        delta_y += map.getGridSize();
    }
}

void RayCaster::castProjectionLine_horizontal_left(int x,
                                                   int y,
                                                   double alpha,
                                                   double beta,
                                                   ObjectInfo& object_info){
    int delta_x = x%map.getGridSize();
    double lambda = (alpha <= M_PI) ? alpha - M_PI/2 : 3*M_PI/2 - alpha;
    bool ray_pointing_up = alpha <= M_PI;
    int y_inverter = (ray_pointing_up) ? -1 : 1;

    while (true) {
        int delta_y = Calculator::calculateDelta(delta_x, lambda) * y_inverter;
        if (outOfBounds(map, x-delta_x, false))
            return;

        int y_factor = calculateBorderFactor(ray_pointing_up, y+delta_y);
        if (map.wallAtGrid(x-delta_x, y+delta_y, -1, y_factor)) {
            //printf("Se encontro una pared en la celda: (%d, %d) con un rayo horizontal hacia la izquierda",
                   //grid_coordinates.first, grid_coordinates.second);
            fillRayInfo(beta, x, y, -delta_x, delta_y, object_info,
                        -1, y_factor);
            return;
        }
        delta_x += map.getGridSize();
    }
}

void RayCaster::castProjectionLine_horizontal_right(int x,
                                                    int y,
                                                    double alpha,
                                                    double beta,
                                                    ObjectInfo& object_info) {
    int delta_x = map.getGridSize() - x % map.getGridSize();
    double lambda = (alpha <= M_PI / 2) ? M_PI / 2 - alpha : alpha -
                                                             3 * M_PI / 2;
    bool ray_pointing_up = alpha <= M_PI;
    int y_inverter = (ray_pointing_up) ? -1 : 1;
    while (true) {
        int delta_y = Calculator::calculateDelta(delta_x, lambda) * y_inverter;
        if (outOfBounds(map, x + delta_x, false))
            return;

        int y_factor = calculateBorderFactor(ray_pointing_up, y + delta_y);
        if (map.wallAtGrid(x + delta_x, y + delta_y, 0, y_factor)) {
            //printf("Se encontro una pared en la celda: (%d, %d) con un rayo horizontal hacia la derecha",
            //grid_coordinates.first, grid_coordinates.second);
            fillRayInfo(beta, x, y, delta_x, delta_y, object_info, 0,
                        y_factor);
            return;
        }
        delta_x += map.getGridSize();
    }
}

bool RayCaster::outOfBounds(ClientMap& map, int pos, bool is_vertical) {
    if (is_vertical)
        return map.outOfVerticalBounds(pos);
    return map.outOfHorizontalBounds(pos);
}

void RayCaster::fillRayInfo(double beta,
                            int x_pos,
                            int y_pos,
                            int delta_x,
                            int delta_y,
                            ObjectInfo& object_info,
                            int x_factor,
                            int y_factor) {
    double final_distance = Calculator::calculateDistance(delta_x, delta_y)
            * cos(beta);
    if (final_distance >= object_info.getHitDistance()
                                && object_info.getHitDistance() != 0)
        return;
    object_info.setHitDistance(final_distance);
    map.getMapInfoForObject(object_info, x_pos + delta_x, y_pos + delta_y,
                            x_factor, y_factor);
    double hit_grid_pos = ((x_pos+delta_x)%GRID_SIZE == 0) ?
           double ((y_pos+delta_y)%GRID_SIZE)/GRID_SIZE :
           double ((x_pos+delta_x)%GRID_SIZE)/GRID_SIZE;
    object_info.setHitGridPos(hit_grid_pos);
}

int RayCaster::calculateBorderFactor(bool should_decrease, int position) {
    if (!should_decrease || position%map.getGridSize() != 0)
        return 0;
    return -1;
}

void RayCaster::saveRayInformation(double ray_angle, double distance) {
    //printf("Se agrega el angulo %f, con distancia %f\n", ray_angle, distance);
    double real_distance = distance/cos(ray_angle);
    wall_distance_info.insert(std::pair<double, double>(ray_angle,
                                                        real_distance));
    angles_list.push_back(ray_angle);
}

void RayCaster::setDimensions(int width, int height) {
    drawing_assistant.setDimensions(width, height);
}