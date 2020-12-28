//
// Created by andy on 27/11/20.
//

#include "client/ray_caster.h"
#include <cmath>
#include <thread>

#define PROJECTION_PLANE_WIDTH 320
#define PROJECTION_PLANE_HEIGHT 200
#define FOV_ANGLE 60
#define GRID_SIZE 64

RayCaster::RayCaster(SdlWindow& window, ClientMap& map) : window(window), map(map) {}

void RayCaster::render3DScreen(int x, int y, double alpha) {
    //printf("Ingresa el jugador en pos (%d, %d), con angulo %f\n", x, y, alpha);
    //printf("Se inicia el recorrido en: %f\n", angle);
    window.fill();
    renderFloorAndCeiling(x, y, alpha);
    renderWalls(x, y, alpha);
    loadObjects(x, y, alpha);
    window.render();
    ray_information.clear();
    angles_list.clear();
}

double calculateBeta(double new_angle, double original_angle) {
    if (std::abs(new_angle - original_angle) <= 0.523599)
        return new_angle - original_angle;
    return 2*M_PI + (new_angle - original_angle);
}

void RayCaster::renderFloorAndCeiling(int x, int y, double alpha) {
    double angle = normalize(alpha + 0.523599);
    for (int ray = 0; ray < PROJECTION_PLANE_WIDTH; ++ray) {
        //printf("Con el jugador en (%d, %d), ", grid.first, grid.second);
        //printf("Se lanza el rayo %d, con el angulo %f\n", i, angle);
        DrawingInfo drawing_info{};
        double beta = calculateBeta(angle, alpha);
        castProjectionLine(x, y, angle, beta, drawing_info);
        window.putFloorAndCeiling(ray, drawing_info);
        angle -= ray_angle_delta;
        if (angle < 0) {
            angle += 2*M_PI;
            alpha += 2*M_PI;
        }
    }
}

void RayCaster::renderWalls(int x, int y, double alpha) {
    double angle = normalize(alpha + 0.523599);
    for (int ray = 0; ray < PROJECTION_PLANE_WIDTH; ++ray) {
        //printf("Con el jugador en (%d, %d), ", grid.first, grid.second);
        //printf("Se lanza el rayo %d, con el angulo %f\n", i, angle);
        DrawingInfo drawing_info{};
        double beta = calculateBeta(angle, alpha);
        castProjectionLine(x, y, angle, beta, drawing_info);
        window.putWall(ray, drawing_info);
        angle -= ray_angle_delta;
        if (angle < 0) {
            angle += 2*M_PI;
            alpha += 2*M_PI;
        }
    }
}

void RayCaster::castProjectionLine(int x,
                                   int y,
                                   double alpha,
                                   double beta,
                                   DrawingInfo& drawing_info) {
    castProjectionLine_vertical(x, y, alpha, beta, drawing_info);
    //printf("Distancia vertical encontrada: %f\n", drawing_info.hit_distance);
    castProjectionLine_horizontal(x, y, alpha, beta, drawing_info);
    //printf("Distancia horizontal encontrada: %f\n", drawing_info.hit_distance);
    //printf("Para el angulo %f se devuelve la distancia: %f\n",beta, drawing_info.hit_distance);
    saveRayInformation(beta, drawing_info.hit_distance);
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
    double lambda = (alpha > M_PI/2) ? M_PI - alpha : alpha;
    bool ray_pointing_left = alpha >= M_PI/2;
    int x_inverter = (ray_pointing_left) ? -1 : 1;
    while (true) {
        int delta_x = calculateDelta(delta_y, lambda) * x_inverter;
        if (outOfBounds(map, y-delta_y, true))
            return;

        int x_factor = calculateBorderFactor(ray_pointing_left, x+delta_x);
        if (map.wallAtGrid(x+delta_x, y-delta_y, x_factor, -1)) {
            //printf("Se encontro una pared en la celda: (%d, %d) con un rayo vertical hacia arriba",
                   //grid_coordinates.first, grid_coordinates.second);
            fillDrawingInfo(beta, x, y, delta_x, -delta_y, drawing_info,
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
                                                   DrawingInfo& drawing_info) {
    int delta_y = map.getGridSize()-y%map.getGridSize();
    double lambda = (alpha <= 3*M_PI/2) ? alpha - M_PI : 2*M_PI - alpha;
    bool ray_pointing_right = alpha <= 3*M_PI/2;
    int x_inverter = (ray_pointing_right) ? -1 : 1;
    while (true) {
        int delta_x = calculateDelta(delta_y, lambda) * x_inverter;
        if (outOfBounds(map, y+delta_y, true))
            return;

        int x_factor = calculateBorderFactor(ray_pointing_right, x+delta_x);
        if (map.wallAtGrid(x+delta_x, y+delta_y, x_factor, 0)) {
            //printf("Se encontro una pared en la celda: (%d, %d) con un rayo vertical hacia abajo",
                   //grid_coordinates.first, grid_coordinates.second);
            fillDrawingInfo(beta, x, y, delta_x, delta_y, drawing_info,
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
                                                     DrawingInfo& drawing_info){
    int delta_x = x%map.getGridSize();
    double lambda = (alpha <= M_PI) ? alpha - M_PI/2 : 3*M_PI/2 - alpha;
    bool ray_pointing_up = alpha <= M_PI;
    int y_inverter = (ray_pointing_up) ? -1 : 1;

    while (true) {
        int delta_y = calculateDelta(delta_x, lambda) * y_inverter;
        if (outOfBounds(map, x-delta_x, false))
            return;

        int y_factor = calculateBorderFactor(ray_pointing_up, y+delta_y);
        if (map.wallAtGrid(x-delta_x, y+delta_y, -1, y_factor)) {
            //printf("Se encontro una pared en la celda: (%d, %d) con un rayo horizontal hacia la izquierda",
                   //grid_coordinates.first, grid_coordinates.second);
            fillDrawingInfo(beta, x, y, -delta_x, delta_y, drawing_info,
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
                                                    DrawingInfo& drawing_info) {
    int delta_x = map.getGridSize() - x % map.getGridSize();
    double lambda = (alpha <= M_PI / 2) ? M_PI / 2 - alpha : alpha -
                                                             3 * M_PI / 2;
    bool ray_pointing_up = alpha <= M_PI;
    int y_inverter = (ray_pointing_up) ? -1 : 1;
    while (true) {
        int delta_y = calculateDelta(delta_x, lambda) * y_inverter;
        if (outOfBounds(map, x + delta_x, false))
            return;

        int y_factor = calculateBorderFactor(ray_pointing_up, y + delta_y);
        if (map.wallAtGrid(x + delta_x, y + delta_y, 0, y_factor)) {
            //printf("Se encontro una pared en la celda: (%d, %d) con un rayo horizontal hacia la derecha",
            //grid_coordinates.first, grid_coordinates.second);
            fillDrawingInfo(beta, x, y, delta_x, delta_y, drawing_info, 0,
                            y_factor);
            return;
        }
        delta_x += map.getGridSize();
    }
}

int RayCaster::calculateDelta(int delta_coord, double delta_alpha) {
    return (int) (delta_coord/tan(delta_alpha));
}

bool RayCaster::outOfBounds(ClientMap& map, int pos, bool is_vertical) {
    if (is_vertical)
        return map.outOfVerticalBounds(pos);
    return map.outOfHorizontalBounds(pos);
}

double RayCaster::calculateDistance(int delta_x, int delta_y) {
    //printf("val x: %d\n", delta_x);
    //printf("val y:%d\n", delta_y);
    return sqrt(pow(delta_x, 2)+pow(delta_y, 2));
}

void RayCaster::fillDrawingInfo(double beta,
                                int x_pos,
                                int y_pos,
                                int delta_x,
                                int delta_y,
                                DrawingInfo& drawing_info,
                                int x_factor,
                                int y_factor) {
    double final_distance = calculateDistance(delta_x, delta_y) * cos(beta);
    if (final_distance >= drawing_info.hit_distance
                                && drawing_info.hit_distance != 0)
        return;
    drawing_info.hit_distance = final_distance;
    drawing_info.hit_x = x_pos+delta_x;
    drawing_info.hit_y = y_pos+delta_y;
    map.getObjectInfo(drawing_info, x_pos+delta_x, y_pos+delta_y, x_factor,
                      y_factor);
    drawing_info.hit_grid_pos = (drawing_info.hit_x%GRID_SIZE == 0) ?
           double (drawing_info.hit_y%GRID_SIZE)/GRID_SIZE :
           double (drawing_info.hit_x%GRID_SIZE)/GRID_SIZE;
}

int RayCaster::calculateBorderFactor(bool should_decrease, int position) {
    if (!should_decrease || position%map.getGridSize() != 0)
        return 0;
    return -1;
}

void RayCaster::loadObjects(int x, int y, double player_angle) {
    //puts("Cargando objetos");
    std::vector<Drawable> objects_vector = map.getAllObjects();
    for (auto& object : objects_vector) {
        double object_angle = getObjectAngle(x, y, object.getMapPosition());
        printf("El jugador mira en angulo %f\n", player_angle);
        printf("Se encuentra objeto %d en angulo respecto del jugador %f\n", object.getObjectType(), object_angle);
        if (shouldDraw(player_angle, object_angle)) {
            renderObject(x, y, player_angle, object_angle, object);
        }
        else
            puts("No se dibuja el objeto");
    }
}

bool RayCaster::shouldDraw(double player_angle, double object_angle) {
    double fov_starting_angle = normalize(player_angle + 0.523599);
    double fov_finishing_angle = normalize(player_angle - 0.523599);
    if (fov_finishing_angle > fov_starting_angle)
        return object_angle >= fov_finishing_angle ||
               object_angle <= fov_starting_angle;
    return object_angle >= fov_finishing_angle &&
           object_angle <= fov_starting_angle;
}

double RayCaster::getObjectAngle(int p_x, int p_y, std::pair<int, int> o_pos) {
    int o_x = o_pos.first;
    int o_y = o_pos.second;
    printf("Objeto en: (%d, %d)\n", o_x, o_y);
    printf("Jugador en: (%d, %d)\n", p_x, p_y);
    int delta_x = o_x - p_x;
    int delta_y = p_y - o_y;
    return normalize(atan2(delta_y, delta_x));
}

double RayCaster::normalize(double alpha) {
    if (alpha >= 2*M_PI)
        return alpha - 2*M_PI;
    if (alpha < 0)
        return alpha + 2*M_PI;
    return alpha;
}

double getObjectAngleRelativeToPlayer(double player_angle, double object_angle){
    if (std::abs(player_angle-object_angle) <= 0.523599)
        return player_angle - object_angle;
    if (player_angle > object_angle)
        return player_angle - object_angle - 2*M_PI;
    return 2*M_PI - (object_angle - player_angle);
}

bool RayCaster::blockedByWall(double angle, double distance) {
    double nearest_distance = 0;
    double angle_found = 0;
    if (ray_information.find(angle) != ray_information.end()) {
        nearest_distance = ray_information.at(angle);
        angle_found = angle;
    } else {
        for (int i = 0; i < angles_list.size()-1; ++i) {
            double angle_1 = angles_list[i];
            double angle_2 = angles_list[i+1];
            if (angle_1 > angle and angle_2 < angle) {
                double diff_1 = angle_1 - angle;
                double diff_2 = angle - angle_2;
                nearest_distance = (diff_1 < diff_2) ?
                      ray_information.at(angle_1) : ray_information.at(angle_2);
                angle_found = (diff_1 < diff_2) ? angle_1 : angle_2;
                break;
            }
        }
    }
    //printf("Distancia mas cercana encontrada: %f\n", nearest_distance);
    nearest_distance /= cos(angle_found);
    //printf("Distancia mas cercana final: %f\n", nearest_distance);
    bool object_blocked = nearest_distance < distance;
    if (object_blocked) {
        //printf("Objeto bloqueado por una pared a distancia %f\n", nearest_distance);
        //printf("Distancia del objeto: %f\n", distance);
        //printf("Angulo del objeto: %f\n", angle);
        //printf("Angulo usado: %f\n", angle_found);
        //printf("No se dibuja el objeto\n");
    }
    return object_blocked;
}

double convertToBeta(double pl_ob_angle) {
    return -pl_ob_angle;
}

void RayCaster::renderObject(int x_pos, int y_pos, double player_angle,
                             double object_angle, Drawable& object) {
    //puts("Se dibujara el objeto");
    std::pair<int, int> object_position = object.getMapPosition();
    int object_x = object_position.first;
    int object_y = object_position.second;
    double pl_ob_angle =
            getObjectAngleRelativeToPlayer(player_angle, object_angle);
    double distance = calculateDistance(x_pos - object_x, y_pos - object_y);
    double beta = convertToBeta(pl_ob_angle);
    if (blockedByWall(beta, distance))
        return;
    //puts("Se dibuja el objeto");
    window.put3DObject(distance, pl_ob_angle, object);
}

void RayCaster::saveRayInformation(double ray_angle, double distance) {
    //printf("Se agrega el angulo %f, con distancia %f\n", ray_angle, distance);
    ray_information.insert(std::pair<double, double>(ray_angle, distance));
    angles_list.push_back(ray_angle);
}