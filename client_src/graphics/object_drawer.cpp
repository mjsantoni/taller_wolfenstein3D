//
// Created by andy on 4/12/20.
//

#include "client/graphics/object_drawer.h"

ObjectDrawer::ObjectDrawer(SdlWindow& _window,
                           ObjectInfoProvider& _object_info_provider,
                           std::map<double, double>& _wall_distance_info,
                           std::map<int, std::pair<int, int>>& _floor_info,
                           std::vector<double>& _angles_list,
                           ClientMap& _map,
                           TextureManager& texture_manager) :
       object_info_provider(_object_info_provider), window(_window),
       wall_distance_info(_wall_distance_info), map(_map),
       floor_info(_floor_info), angles_list(_angles_list),
       drawing_assistant(window, texture_manager) {
}

void ObjectDrawer::loadObjects(int x, int y, double player_angle) {
    //puts("Cargando objetos");
    std::vector<Drawable> objects_vector = map.getAllObjectsAndEnemies();
    //std::cout << "Cant objetos: " << objects_vector.size() << std::endl;
    //std::cout << "jugador en: " << x << "," << y <<")\n";
    for (auto& object : objects_vector) {
        std::cout << "objeto en: " << object.getMapPosition().first << "," << object.getMapPosition().second <<")\n";;
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
    int delta_x = x_pos - object_x;
    int delta_y = object_y - y_pos;
    double pl_ob_angle =
            getGammaAngle(player_angle, object_angle);
    //printf("El angulo del objeto relativo a la vision del jugador es de %f\n", pl_ob_angle);
    double distance = Calculator::calculateDistance(x_pos - object_x,
                                                    y_pos -object_y);
    double beta = convertToBeta(pl_ob_angle);
    //std::cout << "Jugador en (" << x_pos << "," << y_pos << ")\n";
    //std::cout << "Objeto en (" << object_x << "," << object_y << ")\n";
    //std::cout << "Distancia: " << distance << std::endl;
    if (blockedByWall(beta, distance))
        return;
    //printf("Se dibuja el objeto %s\n", object.getObjectName().c_str());
    ObjectInfo object_info =
            object_info_provider.getObjectInfo(object.getObjectType());
    object_info.setHitDistance(distance);
    object_info.setHitGridPos(x_prop);
    object_info.setSpriteAnimationNo(object.getSpriteAnimationNo());
    //std::cout << "Sprite Animation: " << object_info.getSpriteAnimationNo() << std::endl;
    //pl_ob_angle = getGammaAngle(x_pos - object_x, object_y - y_pos, player_angle);
    drawing_assistant.put3DObject(object_info, pl_ob_angle);
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
    int object_width = getObjectWidth(object);
    double phi = Calculator::normalize(starting_fov_angle + 3*M_PI/2);
    int delta_x = std::round(cos(phi)*object_width);
    int delta_y = std::round(sin(phi)*object_width*-1);
    int object_final_x = object_starting_x + delta_x;
    int object_final_y = object_starting_y + delta_y;
    return std::pair<int, int>{object_final_x, object_final_y};
}

int ObjectDrawer::getObjectWidth(Drawable& drawable) {
    int object_type = drawable.getObjectType();
    ObjectInfo object_info = object_info_provider.getObjectInfo(object_type);
    return (int) (object_info.getObjectWidth() * map_grid_size);
}

bool ObjectDrawer::shouldDraw(double player_angle,
                              double os_angle,
                              double of_angle,
                              double& diff_angle) {
    //printf("El objeto empieza en angulo: %f\n", os_angle);
    //printf("El objeto finaliza en angulo: %f\n", of_angle);
    double fov_starting_angle = Calculator::normalize(player_angle + 0.523599);
    double fov_finishing_angle = Calculator::normalize(player_angle - 0.523599);
    //printf("La FOV se chequea desde: %f\n", fov_starting_angle);
    //printf("La FOV se chequea hasta: %f\n", fov_finishing_angle);
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
/*
double ObjectDrawer::getGammaAngle(int delta_x, int delta_y, double  player_angle) {
    double object_angle = atan2(delta_y, delta_x);
    return object_angle - player_angle;
}
*/
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
    //nearest_distance /= cos(angle_found);
    //printf("Distancia mas cercana final: %f\n", nearest_distance);
    bool object_blocked = nearest_distance < distance;
    if (object_blocked) {
        printf("Objeto bloqueado por una pared a distancia %f\n", nearest_distance);
        printf("Distancia del objeto: %f\n", distance);
        printf("Angulo del objeto: %f\n", angle);
        printf("Angulo usado: %f\n", angle_found);
        printf("No se dibuja el objeto\n");
    }
    return object_blocked;
}

void ObjectDrawer::setDimensions(int width, int height) {
    drawing_assistant.setDimensions(width, height);
}


