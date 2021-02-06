//
// Created by andy on 4/12/20.
//

#include "client/graphics/object_drawer.h"

#define PROJECTION_PLANE_width 320
#define PROJECTION_PLANE_height 200
#define MAX_OBJECT_HEIGHT 300

ObjectDrawer::ObjectDrawer(SdlWindow& _window,
                           ObjectInfoProvider& _object_info_provider,
                           std::map<double, double>& _wall_distance_info,
                           std::map<int, std::pair<int, int>>& _floor_info,
                           std::vector<double>& _angles_list,
                           ClientMap& _map) :
       object_info_provider(_object_info_provider), window(_window),
       wall_distance_info(_wall_distance_info), map(_map),
       floor_info(_floor_info), angles_list(_angles_list) {
    map_grid_size = map.getGridSize();
}

void ObjectDrawer::loadObjects(int x, int y, double player_angle) {
    //puts("Cargando objetos");
    std::vector<Drawable> objects_vector = map.getAllObjects();
    for (auto& object : objects_vector) {
        //printf("El objeto %s empieza en la posicion: (%d,%d)\n", object.getObjectName().c_str(), object.getMapPosition().first, object.getMapPosition().second);
        double object_starting_angle =
                getObjectAngle(x, y, object.getMapPosition());
        std::pair<int, int> object_final_pos = projectObjectOnMap(object,
                                                                  player_angle);
        //printf("El objeto %s termina en la posicion: (%d,%d)\n", object.getObjectName().c_str(), object_final_pos.first, object_final_pos.second);
        double object_final_angle = getObjectAngle(x, y, object_final_pos);
        //printf("El jugador mira en direccion: %f\n", player_angle);
        //printf("Se encuentra objeto %s en angulo %f respecto de la posicion del jugador\n", object.getObjectName().c_str(), object_starting_angle);
        double diff_angle = 0;
        if (shouldDraw(player_angle,object_starting_angle, object_final_angle,
                       diff_angle)){
            //printf("El objeto %s entra en la vision del jugador\n", object.getObjectName().c_str());
            //printf("Diff angle: %f\n", diff_angle);
            double x_prop = calculateObjectStartingXPos(object_starting_angle,
                                                        object_final_angle, diff_angle);
            renderObject(x, y, player_angle, object_starting_angle + diff_angle,
                         x_prop, object);
        }
        //else
            //puts("No se dibuja el objeto: no entra en el angulo de vision");
    }
}

Area ObjectDrawer::findObjectProportions(ObjectInfo& object_info,
                                         double pl_ob_angle) {
    double distance = object_info.getHitDistance();
    distance *= cos(pl_ob_angle);
    //printf("Distancia del objeto: %f\n", distance);
    int x_pos = findXPosForObject(pl_ob_angle,
                          (int) (object_info.getObjectWidth() * map_grid_size));
    int object_height = findObjectHeight(distance,
                         (int) (object_info.getObjectHeight() * map_grid_size));
    int object_width = findObjectWidth(distance,
                          (int) (object_info.getObjectWidth() * map_grid_size));
    int ray_no = findRayNumberForAngle(pl_ob_angle);
    int y_pos = findYPosForObject(ray_no, pl_ob_angle, distance, object_height);
    //printf("Se tiene un objeto con angulo de %f respecto al angulo en el que mira el jugador\n", pl_ob_angle);
    //printf("Se dibuja al objeto en la pos x: %d\n", x_pos);
    //printf("Se dibuja al objeto en la pos y: %d", y_pos);
    //printf(" con el piso empezando en la pos %d\n", floor_starting_point);
    //printf("Distancia del objeto: %f\n", distance);
    Area area(x_pos, y_pos, object_width, object_height);
    return area;
    //printf("Altura del objeto: %d\n", drawing_info.object_height);
}

int ObjectDrawer::findXPosForObject(double pl_ob_beta, int object_width) {
    double fov_x_pos = double(pl_ob_beta + 0.523599) / 1.0472;
    double proj_plane_x_pos = fov_x_pos* PROJECTION_PLANE_width;
    double proj_plane_centered  = proj_plane_x_pos - double (object_width);
    int x_screen_pos = int (proj_plane_centered * width_prop);
    return x_screen_pos;
}

int ObjectDrawer::findYPosForObject(int ray_no,
                                    double pl_ob_angle,
                                    double distance,
                                    int object_height){
    std::pair<int, int> ray_floor_info = floor_info.at(ray_no);
    int floor_starting_point = ray_floor_info.first;
    int floor_height = ray_floor_info.second;
    //printf("El suelo empieza en %d\n", floor_starting_point);
    //auto y_floor_proportion = (double) object_height/floor_height;
    //int y_floor_position = int (y_floor_proportion * floor_height);
    //int screen_position = floor_starting_point + object_height;
    //int centered_screen_pos = screen_position - object_height;
    /*
    int y_pos = floor_starting_point + safe_distance +
            ((floor_height - object_height) / floor_height) * floor_height;
    int safe_position = floor_starting_point + safe_distance;
    y_pos = (y_pos > safe_position) ? y_pos : safe_position;
    printf("Distancia del objeto: %f\n", distance);
    printf("Altura del objeto: %d\n", object_height);
    printf("Pos y: %d\n", y_pos);
    printf("Distancia del suelo y: %d\n", y_pos - floor_starting_point);
    return y_pos;
    */
    double wall_distance = findWallDistanceForAngle(-pl_ob_angle);
    double object_to_wall_distance = wall_distance - distance;
    double dist_proportion = object_to_wall_distance/wall_distance;
    int floor_position = (int) (dist_proportion * floor_height);
    int y_pos = floor_starting_point + floor_position - object_height;
    return y_pos;
}

int ObjectDrawer::findObjectHeight(double distance, int object_height) {
    if (distance <= 45)
        distance = 45;
    double object_wall_prop = (double) object_height / map_grid_size;
    double distance_prop = (double) map_grid_size/distance;
    double object_raw_height = object_wall_prop * distance_prop * 255;
    //int object_screen_height = (int) (height_factor*object_raw_height);
    return (int) object_raw_height;
}

int ObjectDrawer::findObjectWidth(double distance, int object_width) {
    double object_width_prop = (double) object_width / map_grid_size;
    int wall_width_for_distance = (int) ((double) 100/distance * 188);
    double object_raw_width = object_width_prop*wall_width_for_distance;
    int object_screen_width = (int) (width_prop*object_raw_width);
    return object_screen_width;
}

int ObjectDrawer::findRayNumberForAngle(double beta) {
    int counter = 0;
    while (true) {
        beta += 0.00327249;
        if (beta > 0.523599)
            break;
        ++counter;
    }
    return (counter <= 319) ? counter : 319;
}

Area ObjectDrawer::assembleScreenArea(ObjectInfo& object_info,
                                      double pl_ob_angle) {
    Area screen_area =
            findObjectProportions(object_info, pl_ob_angle);
    return screen_area;
}

double ObjectDrawer::findWallDistanceForAngle(double angle) {
    double nearest_distance = 0;
    double angle_found = 0;
    if (wall_distance_info.find(angle) != wall_distance_info.end()) {
        nearest_distance = wall_distance_info.at(angle);
        angle_found = angle;
    } else {
        for (int i = 0; i < angles_list.size()-1; ++i) {
            double angle_1 = angles_list[i];
            double angle_2 = angles_list[i+1];
            if (angle_1 > angle and angle_2 < angle) {
                double diff_1 = angle_1 - angle;
                double diff_2 = angle - angle_2;
                nearest_distance = (diff_1 < diff_2) ?
                                   wall_distance_info.at(angle_1) :
                                   wall_distance_info.at(angle_2);
                angle_found = (diff_1 < diff_2) ? angle_1 : angle_2;
                break;
            }
        }
    }
    if (nearest_distance == 0 && angle_found == 0)
        nearest_distance = wall_distance_info.at(angles_list[0]);
    //printf("Distancia mas cercana encontrada: %f\n", nearest_distance);
    //printf("Primera distancia: %f\n", wall_distance_info.at(angles_list[0]));
    return nearest_distance;
}

double convertToBeta(double pl_ob_angle) {
    return -pl_ob_angle;
}

void ObjectDrawer::renderObject(int x_pos, int y_pos, double player_angle,
                                double object_angle, double x_prop,
                                Drawable& object) {
    //puts("Se dibujara el objeto");
    std::pair<int, int> object_position = object.getMapPosition();
    int object_x = object_position.first;
    int object_y = object_position.second;
    double pl_ob_angle =
            getGammaAngle(player_angle,object_angle);
    //printf("El angulo del objeto relativo a la vision del jugador es de %f\n", pl_ob_angle);
    double distance = Calculator::calculateDistance(x_pos - object_x,
                                                    y_pos -object_y);
    double beta = convertToBeta(pl_ob_angle);
    if (blockedByWall(beta, distance))
        return;
    //printf("Se dibuja el objeto %s\n", object.getObjectName().c_str());
    ObjectInfo object_info =
            object_info_provider.getObjectInfo(object.getObjectType());
    object_info.setHitDistance(distance);
    object_info.setHitGridPos(x_prop);
    put3DObject(object_info, pl_ob_angle);
    //if (isEnemy(object_info))
        //object_info.setSpriteAnimationNo(object_info.getSpriteAnimationNo()+1);
}

double ObjectDrawer::calculateObjectStartingXPos(double os_angle,
                                                 double of_angle,
                                                 double diff_angle) {
    return std::abs(diff_angle/(of_angle-os_angle));
}

std::pair<int, int> ObjectDrawer::projectObjectOnMap(Drawable& object,
                                                     double player_angle) {
    double starting_fov_angle = Calculator::normalize(player_angle + 0.523599);
    std::pair<int, int> object_starting_position = object.getMapPosition();
    int object_starting_x = object_starting_position.first;
    int object_starting_y = object_starting_position.second;
    int object_width = object.getMapWidth();
    double phi = Calculator::normalize(starting_fov_angle + 3*M_PI/2);
    int delta_x = std::round(cos(phi)*object_width);
    int delta_y = std::round(sin(phi)*object_width*-1);
    int object_final_x = object_starting_x + delta_x;
    int object_final_y = object_starting_y + delta_y;
    return std::pair<int, int>{object_final_x, object_final_y};
}

bool ObjectDrawer::shouldDraw(double player_angle,
                              double os_angle,
                              double of_angle,
                              double& diff_angle) {
    //printf("El objeto empieza en angulo: %f\n", os_angle);
    //printf("El objeto finaliza en angulo: %f\n", of_angle);
    double fov_starting_angle = Calculator::normalize(player_angle + 0.523599);
    double fov_finishing_angle = Calculator::normalize(player_angle - 0.523599);
    if (fov_finishing_angle >= fov_starting_angle)
        return shouldDraw_borderCase(os_angle, of_angle, fov_starting_angle,
                                     fov_finishing_angle, diff_angle);
    double sc_angle = (fov_starting_angle > fov_finishing_angle) ?
                      fov_finishing_angle : fov_starting_angle;
    double fc_angle = (fov_starting_angle > fov_finishing_angle) ?
                      fov_starting_angle: fov_finishing_angle;
    //printf("La FOV se chequea desde: %f\n", sc_angle);
    //printf("La FOV se chequea hasta: %f\n", fc_angle);
    bool sa_included = (os_angle >= sc_angle && os_angle <= fc_angle);
    bool fa_included = (of_angle >= sc_angle && of_angle <= fc_angle);
    if (sa_included)
        diff_angle = 0;
    else
        diff_angle = std::abs(fc_angle - os_angle);
    return sa_included || fa_included;
}

bool ObjectDrawer::shouldDraw_borderCase(double os_angle,
                                         double of_angle,
                                         double fov_starting_angle,
                                         double fov_finishing_angle,
                                         double& diff_angle) {
    bool sa_included = (os_angle >= fov_finishing_angle ||
                        os_angle <= fov_starting_angle);
    bool fa_included = (of_angle >= fov_finishing_angle ||
                        of_angle <= fov_starting_angle);
    if (sa_included)
        diff_angle = 0;
    else
        diff_angle = std::abs(os_angle - fov_finishing_angle);
    return sa_included || fa_included;
}

double ObjectDrawer::getObjectAngle(int p_x, int p_y, std::pair<int, int> o_pos) {
    int o_x = o_pos.first;
    int o_y = o_pos.second;
    //printf("Objeto en: (%d, %d)\n", o_x, o_y);
    //printf("Jugador en: (%d, %d)\n", p_x, p_y);
    int delta_x = o_x - p_x;
    int delta_y = p_y - o_y;
    return Calculator::normalize(atan2(delta_y, delta_x));
}

double ObjectDrawer::getGammaAngle(double player_angle, double object_angle) {
    if (std::abs(player_angle-object_angle) <= M_PI)
        return player_angle - object_angle;
    if (player_angle > object_angle)
        return (player_angle - object_angle) - 2*M_PI;
    return 2*M_PI - (object_angle - player_angle);
}

bool ObjectDrawer::blockedByWall(double angle, double distance) {
    double nearest_distance = 0;
    double angle_found = 0;
    if (wall_distance_info.find(angle) != wall_distance_info.end()) {
        nearest_distance = wall_distance_info.at(angle);
        angle_found = angle;
    } else {
        for (int i = 0; i < angles_list.size()-1; ++i) {
            double angle_1 = angles_list[i];
            double angle_2 = angles_list[i+1];
            if (angle_1 > angle and angle_2 < angle) {
                double diff_1 = angle_1 - angle;
                double diff_2 = angle - angle_2;
                nearest_distance = (diff_1 < diff_2) ?
                                   wall_distance_info.at(angle_1) :
                                   wall_distance_info.at(angle_2);
                angle_found = (diff_1 < diff_2) ? angle_1 : angle_2;
                break;
            }
        }
    }
    if (nearest_distance == 0 && angle_found == 0)
        return false;
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

void ObjectDrawer::setDimensions(int width, int height) {
    window_width = width;
    window_height = height;
    width_prop = width/320;
    height_prop = (int) (height/(0.8*200));
}

void ObjectDrawer::put3DObject(ObjectInfo& object_info, double pl_ob_angle) {
    Area image_area;
    SdlTexture sdl_texture(object_info.getImagePath());
    SDL_Texture* texture =
            sdl_texture.loadTexture(window.getRenderer(), image_area);
    image_area.setX((int) object_info.getHitGridPos() * image_area.getWidth());
    Area screen_area = assembleScreenArea(object_info, pl_ob_angle);
    window.loadImage(texture, image_area, screen_area);
    SDL_DestroyTexture(texture);
    //printf("Nombre de objeto: %s\n", object_info.getObjectName().c_str());
    //printf("Distancia: %f\n", distance);
    //printf("Pos x: %d\n", screen_area.getX());
    //printf("Pos y: %d\n", screen_area.getY());
    //printf("Altura: %d\n", screen_area.getHeight());
    //printf("Ancho: %d\n", screen_area.getWidth());
}


