//
// Created by andy on 10/2/21.
//

#include <client/graphics/sprite_drawer.h>
#include "client/graphics/object_drawing_assistant.h"

#define PROJECTION_PLANE_width 320
#define PROJECTION_PLANE_height 200
#define MAX_OBJECT_HEIGHT 300
#define ANCHO_TEXT 64

ObjectDrawingAssistant::ObjectDrawingAssistant(
        SdlWindow& _window,
        std::map<double, double>& _wall_distance_info,
        std::map<int, std::pair<int, int>>& _floor_info,
        std::vector<double>& _angles_list) :
        window(_window),
        wall_distance_info(_wall_distance_info),
        floor_info(_floor_info),
        angles_list(_angles_list) {
}

void ObjectDrawingAssistant::put3DObject(ObjectInfo& object_info,
                                         double pl_ob_angle) {
    Area image_area;
    SDL_Texture* image = getObjectImage(object_info, image_area);
    image_area.setX((int) object_info.getHitGridPos() * image_area.getWidth());
    Area screen_area = assembleScreenArea(object_info, pl_ob_angle);
    window.loadImage(image, image_area, screen_area);
    SDL_DestroyTexture(image);
    //printf("Nombre de objeto: %s\n", object_info.getObjectName().c_str());
    //printf("Distancia: %f\n", object_info.getHitDistance());
    //printf("Pos x: %d\n", screen_area.getX());
    //printf("Pos y: %d\n", screen_area.getY());
    //printf("Altura: %d\n", screen_area.getHeight());
    //printf("Ancho: %d\n", screen_area.getWidth());
    //printf("Ancho de pantalla: %d\n", window_width);
}

SDL_Texture*
ObjectDrawingAssistant::getObjectImage(ObjectInfo& o_i, Area& image_area) {
    if (!o_i.isSprite()) {
        SdlTexture sdl_texture(o_i.getImagePath());
        SDL_Texture* texture =
                sdl_texture.loadTexture(window.getRenderer(), image_area);
        return texture;
    }
    SdlSprite sdl_sprite(o_i.getImagePath(), o_i.getImageWidth(),
                         o_i.getImageHeight(), o_i.getSpriteCols(),
                         o_i.getSpriteRows(), o_i.getSpriteHPadding(),
                         o_i.getSpriteVPadding());
    SDL_Texture* texture = sdl_sprite.loadTexture(window.getRenderer(),
                                                  image_area, o_i.getSpriteAnimationNo());
    return texture;
}

Area ObjectDrawingAssistant::findObjectProportions(ObjectInfo& object_info,
                                             double pl_ob_angle) {
    double distance = object_info.getHitDistance();
    distance *= cos(pl_ob_angle);
    //printf("Distancia del objeto: %f\n", distance);
    /*
    int object_width = findObjectWidth(distance,
                                       (int) (object_info.getObjectWidth() * map_grid_size));
    int object_height = findObjectHeight(distance,
                                         (int) (object_info.getObjectHeight() * map_grid_size));
    int original_width = object_width;
    SpriteDrawer::findLimitsForObject(object_info.getObjectType(), object_width, object_height);
    int x_pos;
    if (object_width < original_width) {
        std::cout << "ENTRO IF\n";
        std::cout << "Angulo: " << pl_ob_angle << std::endl;
        std::cout << "AAAAAAAA\n";
        std::cout << "ancho original: " << original_width << std::endl;
        std::cout << "ancho actual: " << object_width << std::endl;
        x_pos = findXPosForObject(pl_ob_angle, original_width);
        std::cout << "X pos original: " << x_pos << std::endl;
        x_pos = findXPosForNearObject(pl_ob_angle, original_width, object_width);
        std::cout << "X pos modificada: " << x_pos << std::endl;
    } else {
        std::cout << "ENTRO ELSE\n";
        x_pos = findXPosForObject(pl_ob_angle, object_width);
        std::cout << "X pos sin modificar: " << x_pos << std::endl;
    }
    //if (x_pos + object_width >= window_width - 10)
    //object_width = window_width - x_pos - 10;
    int ray_no = findRayNumberForAngle(pl_ob_angle);
    int y_pos = findYPosForObject(ray_no, pl_ob_angle, distance, object_height);

    int object_real_height = (int) (object_info.getObjectHeight() * 64);
    std::cout << "Object real height: " << object_real_height << std::endl;
    int object_real_width = (int) (object_info.getObjectWidth() * 64);
    std::cout << "Object real width: " << object_real_width << std::endl;
    int x_pos = findXPosForObject(pl_ob_angle);
    int object_height = findObjectHeight(distance, object_real_height);
    int y_pos = findYPosForObject(object_height);
    int object_width = findObjectWidth(object_real_width);
    //printf("Se tiene un objeto con angulo de %f respecto al angulo en el que mira el jugador\n", pl_ob_angle);
    //printf("Se dibuja al objeto en la pos x: %d\n", x_pos);
    //printf("Se dibuja al objeto en la pos y: %d", y_pos);
    //printf(" con el piso empezando en la pos %d\n", floor_starting_point);
    printf("Distancia del objeto: %f\n", distance);
     */
    double object_height = findObjectHeight(distance);
    int y0 = findY0(object_height);
    double y1 = y0 + object_height;
    //int col_starting_point = findColumnStartingPoint(wall_height);
    auto col_height = double(y0 - y1);
    double x0 = tan(pl_ob_angle) * VIEW_DIST;
    double object_width = col_height;
    double x = (SCREEN_WIDTH/2 + x0 - object_width/2);
    Area area(x, y1, object_width, col_height);
    return area;
    //printf("Altura del objeto: %d\n", drawing_info.object_height);
}

double ObjectDrawingAssistant::findObjectHeight(double distance) {
    auto height_proportion = (double) OBJECT_HEIGHT/distance;
    return (height_proportion*proj_plane_distance); // altura muro
}

int ObjectDrawingAssistant::findY0(double object_height) {
    return (int (SCREEN_HEIGHT/2) - int (object_height/2));
}



int ObjectDrawingAssistant::findRayNumberForAngle(double beta) {
    int counter = 0;
    while (true) {
        beta += 0.00327249;
        if (beta > 0.523599)
            break;
        ++counter;
    }
    return (counter <= 319) ? counter : 319;
}

Area ObjectDrawingAssistant::assembleScreenArea(ObjectInfo& object_info,
                                          double pl_ob_angle) {
    Area screen_area =
            findObjectProportions(object_info, pl_ob_angle);
    return screen_area;
}

int ObjectDrawingAssistant::findObjectHeight(double distance,
                                             int object_height) {
    std::cout << "distance: " << distance << std::endl;
    auto height_proportion = (double) object_height/distance;
    return (int) (height_proportion*255);
}

int ObjectDrawingAssistant::findYPosForObject(int object_height) {
    return (window_height - object_height)/2;
}

int ObjectDrawingAssistant::findXPosForObject(double pl_ob_angle) {
    return (int) (tan(pl_ob_angle) * 277);
}

int ObjectDrawingAssistant::findObjectWidth(int object_width) {
    return (int) (320-object_width)/2;
}


/*
int ObjectDrawingAssistant::findObjectHeight(double distance, int object_height) {
    double object_wall_prop = (double) object_height / map_grid_size;
    double distance_prop = (double) map_grid_size/distance;
    double object_raw_height = object_wall_prop * distance_prop * 255;
    //int object_screen_height = (int) (height_factor*object_raw_height);
    //if (object_raw_height < object_wall_prop * 250)
        //return (int) (object_wall_prop * 250);
    return (int) object_raw_height;
}

int ObjectDrawingAssistant::findObjectWidth(double distance, int object_width) {
    double object_width_prop = (double) object_width / map_grid_size;
    int wall_width_for_distance = (int) ((double) 100/distance * 188);
    double object_raw_width = object_width_prop*wall_width_for_distance;
    int object_screen_width = (int) (width_factor*object_raw_width);
    //if (object_screen_width < object_width_prop * 700)
    //return (int) (object_width_prop * 700);
    return object_screen_width;
}

int ObjectDrawingAssistant::findXPosForNearObject(double pl_ob_beta, int original_width, int current_width) {
    int original_x_pos = findXPosForObject(pl_ob_beta, original_width);
    return original_x_pos + original_width/2 - current_width/2;
    //
    double fov_x_pos = double(pl_ob_beta + 0.523599) / 1.0472;
    double proj_plane_x_pos = fov_x_pos* PROJECTION_PLANE_width*width_factor;
    double proj_plane_centered  = proj_plane_x_pos + original_width - current_width;
    return (int) proj_plane_centered;
//
}

int ObjectDrawingAssistant::findXPosForObject(double pl_ob_beta, int object_width) {
    double fov_x_pos = double(pl_ob_beta + 0.523599) / 1.0472;
    double proj_plane_x_pos = fov_x_pos* PROJECTION_PLANE_width*width_factor;
    double proj_plane_centered  = proj_plane_x_pos - double (object_width);
    return (int) proj_plane_centered;
}

int ObjectDrawingAssistant::findXPosForObject(double pl_ob_beta, int object_width) {
    double fov_x_pos = double(pl_ob_beta + 0.523599) / 1.0472;
    double proj_plane_x_pos = fov_x_pos* PROJECTION_PLANE_width;
    double proj_plane_centered  = proj_plane_x_pos - double (object_width);
    int x_screen_pos = int (proj_plane_centered * width_factor);
    return x_screen_pos;
}

int ObjectDrawingAssistant::findYPosForObject(int ray_no,
                                        double pl_ob_angle,
                                        double distance,
                                        int object_height){
    std::pair<int, int> ray_floor_info = floor_info.at(ray_no);
    int floor_starting_point = ray_floor_info.first;
    int floor_height = ray_floor_info.second;
    //std::cout << "floor starting point: " << floor_starting_point << std::endl;
    double wall_distance = findWallDistanceForAngle(-pl_ob_angle);
    //std::cout << "distancia de pared encontrada para determinar pos: " << wall_distance << std::endl;
    double object_to_wall_distance = wall_distance - distance;
    double dist_proportion = object_to_wall_distance/(wall_distance+300);
    int floor_position = (int) (dist_proportion * floor_height);
    int y_pos = floor_starting_point + floor_position - object_height;
    //std::cout << "original y pos: " << y_pos << std::endl;
    if (y_pos <= floor_starting_point - object_height) {
        //std::cout << "El objeto se solapa con la pared\n";
        y_pos = floor_starting_point - object_height;
    }
    return y_pos;
}
*/

double ObjectDrawingAssistant::findWallDistanceForAngle(double angle) {
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

void ObjectDrawingAssistant::setDimensions(int width, int height) {
    window_width = width;
    window_height = height;
    width_factor = width/320;
    height_factor = (int) (height/(0.8*200));
}

