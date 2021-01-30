//
// Created by andy on 27/11/20.
//

#include "client/graphics/ray_caster.h"

#include <thread>

#define PROJECTION_PLANE_WIDTH 320
#define PROJECTION_PLANE_HEIGHT 200
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
            angles_list(_angles_list){
    map_grid_size = map.getGridSize();
}

void RayCaster::renderBackground(int x, int y, double alpha) {
    double angle = Calculator::normalize(alpha + 0.523599);
    for (int ray = 0; ray < PROJECTION_PLANE_WIDTH; ++ray) {
        //printf("Con el jugador en (%d, %d), ", grid.first, grid.second);
        //printf("Se lanza el rayo %d, con el angulo %f\n", i, angle);
        ObjectInfo object_info{};
        double beta = Calculator::calculateBeta(angle, alpha);
        castProjectionLine(x, y, angle, beta, object_info);
        object_info = fillObjectInfo(object_info);
        printf("Para el angulo %f se devuelve la distancia: %f\n",beta, object_info.getHitDistance());
        putFloorAndCeiling(ray, object_info);
        putWall(ray, object_info);
        angle -= ray_angle_delta;
        if (angle < 0) {
            angle += 2*M_PI;
            alpha += 2*M_PI;
        }
    }
}

void RayCaster::putFloorAndCeiling(int ray_no, ObjectInfo& object_info) {
    Area screen_area = assembleScreenArea(ray_no, object_info);
    drawFloor(ray_no, screen_area.getY(), screen_area.getHeight());
    drawCeiling(ray_no, screen_area.getY());
}

Area RayCaster::assembleScreenArea(int ray_no, ObjectInfo& object_info) {
    int distance = (int) object_info.getHitDistance();
    int col_height = findColumnHeight(distance);
    int col_starting_point = findColumnStartingPoint(col_height);
    Area screen_area(
            ray_no*width_factor,col_starting_point, width_factor, col_height
    );
    //printf("Rayo %d:Se coloca una pared a distancia %d, en (%d, %d), con un ancho de %d y altura de %d\n",
    //ray_no, distance, ray_no*width_factor, col_starting_point, width_factor, col_height);
    return screen_area;
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
    wall_distance_info.insert(std::pair<double, double>(ray_angle, distance));
    angles_list.push_back(ray_angle);
}

void RayCaster::drawFloor(int x_pos, int wall_posY, int wall_height) {
    int fsp_for_column = wall_posY + wall_height;
    int fh_for_column = window_height - fsp_for_column;
    std::pair<int, int> ray_floor_info {fsp_for_column, fh_for_column};
    floor_info.insert(std::pair<int,std::pair<int,int>>(x_pos, ray_floor_info));
    Area area(x_pos*width_factor, fsp_for_column, width_factor, fh_for_column);
    window.drawRectangle(area, 123, 123, 123, 0);
}

void RayCaster::drawCeiling(int x_pos, int y_pos) {
    Area area(x_pos*width_factor, 0, width_factor, y_pos);
    window.drawRectangle(area, 60, 60, 60, 0);
}

void RayCaster::setDimensions(int width, int height) {
    window_width = width;
    window_height = height;
    width_factor = width / 320;
    height_factor = (int) (height / (0.8 * 200));
}

int RayCaster::findColumnHeight(int distance) {
    auto height_proportion = (double) map_grid_size/distance;
    return (int) (height_proportion*255);
}

int RayCaster::findColumnStartingPoint(int col_height) {
    return (window_height - col_height)/2;
}

void RayCaster::putWall(int ray_no, ObjectInfo& object_info) {
    Area image_area;
    SDL_Texture* texture = loadWallTexture(object_info, image_area);
    Area screen_area = assembleScreenArea(ray_no, object_info);
    window.loadImage(texture, image_area, screen_area);
    SDL_DestroyTexture(texture);
}

SDL_Texture* RayCaster::loadWallTexture(ObjectInfo& object_info,
                                        Area& image_area) {
    SdlTexture sdl_texture(object_info.getImagePath());
    SDL_Texture* image = sdl_texture.loadTexture(window.getRenderer(),
                                                 image_area);
    image_area.setX((int) (object_info.getHitGridPos() *image_area.getWidth()));
    image_area.setWidth(image_area.getWidth()/map_grid_size);
    return image;
}