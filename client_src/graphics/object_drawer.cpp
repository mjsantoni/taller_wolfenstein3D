//
// Created by andy on 4/12/20.
//

#include <client/image_parser.h>
#include "client/object_drawer.h"

#define PROJECTION_PLANE_width 320
#define PROJECTION_PLANE_height 200
#define GRID_SIZE 64
#define MAX_OBJECT_HEIGHT 300

ObjectDrawer::ObjectDrawer() {
    image_parser.fillImageVector(image_info_vector);
}

void ObjectDrawer::setRenderer(SDL_Renderer* window_renderer,
                               int window_width,
                               int window_height) {
    renderer = window_renderer;
    this->window_width = window_width;
    this->window_height = window_height;
    this->width_prop = double (window_width) / PROJECTION_PLANE_width;
    this->height_prop = double (window_height) / PROJECTION_PLANE_height;
}

SDL_Texture* ObjectDrawer::drawImage(DrawingInfo& drawing_info,
                                     Area& image_area) {
    getImageInformation(drawing_info);
    SdlTexture sdl_texture(drawing_info.texture_name);
    SDL_Texture* image = sdl_texture.loadTexture(renderer, image_area);
    return image;
    //printf("Se copiara una pared desde: (%d, %d) con ancho de %d y altura de %d\n", image_area.getX(), image_area.getY(), image_area.getWidth(), image_area.getHeight());
}

SDL_Texture* ObjectDrawer::drawWall(DrawingInfo& drawing_info,
                                     Area& image_area) {
    getImageInformation(drawing_info);
    SdlTexture sdl_texture(drawing_info.texture_name);
    SDL_Texture* image = sdl_texture.loadTexture(renderer, image_area);
    image_area.setX((int) (drawing_info.hit_grid_pos*image_area.getWidth()));
    image_area.setWidth(image_area.getWidth()/GRID_SIZE);
    return image;
    //printf("Se copiara una pared desde: (%d, %d) con ancho de %d y altura de %d\n", image_area.getX(), image_area.getY(), image_area.getWidth(), image_area.getHeight());
}

void ObjectDrawer::drawFloor(int x_pos, int wall_posY, int wall_height) {
    int width_factor = window_width/PROJECTION_PLANE_width;
    int fsp_for_column = wall_posY + wall_height;
    int fh_for_column = window_height - fsp_for_column;
    std::pair<int, int> ray_floor_info {fsp_for_column, fh_for_column};
    floor_info.insert(std::pair<int,std::pair<int,int>>(x_pos, ray_floor_info));
    SDL_Rect floor_rect = {
            x_pos*width_factor, fsp_for_column, width_factor, fh_for_column
    };
    SDL_SetRenderDrawColor(renderer, 123, 123, 123, 0);
    SDL_RenderFillRect(renderer, &floor_rect);
}

void ObjectDrawer::drawCeiling(int x_pos, int y_pos) {
    int width_factor = window_width/PROJECTION_PLANE_width;
    SDL_Rect ceiling_rect = {
            x_pos*width_factor, 0, width_factor, y_pos
    };
    SDL_SetRenderDrawColor(renderer, 60, 60, 60, 0);
    SDL_RenderFillRect(renderer, &ceiling_rect);
}

void ObjectDrawer::findObjectProportions(DrawingInfo& drawing_info,
                                         double distance,
                                         double pl_ob_angle,
                                         Area& screen_area) {
    distance *= cos(pl_ob_angle);
    int x_pos = findXPosForObject(pl_ob_angle, drawing_info.object_width);
    int object_height = findObjectHeight(distance, drawing_info);
    int ray_no = findRayNumberForAngle(pl_ob_angle);
    int y_pos = findYPosForObject(ray_no, distance, object_height);
    int object_width = findObjectWidth(distance, drawing_info);
    printf("Se tiene un objeto con angulo de %f respecto al angulo en el que mira el jugador\n", pl_ob_angle);
    //printf("Se dibuja al objeto en la pos x: %d\n", x_pos);
    //printf("Se dibuja al objeto en la pos y: %d", y_pos);
    //printf(" con el piso empezando en la pos %d\n", floor_starting_point);
    //printf("Distancia del objeto: %f\n", distance);
    screen_area.setX(x_pos);
    screen_area.setY(y_pos);
    screen_area.setWidth(object_width);
    screen_area.setHeight(object_height);
    //printf("Altura del objeto: %d\n", drawing_info.object_height);
}

int ObjectDrawer::findXPosForObject(double pl_ob_beta, int object_width) {
    double fov_x_pos = double(pl_ob_beta + 0.523599) / 1.0472;
    double proj_plane_x_pos = fov_x_pos* PROJECTION_PLANE_width;
    double proj_plane_centered  = proj_plane_x_pos - double (object_width)/2;
    int screen_pos = int (proj_plane_centered * width_prop);
    return screen_pos;
}

int ObjectDrawer::findYPosForObject(int ray_no,
                                    double distance,
                                    int object_height){
    std::pair<int, int> ray_floor_info = floor_info.at(ray_no);
    int floor_starting_point = ray_floor_info.first;
    int floor_height = ray_floor_info.second;
    //auto y_floor_proportion = (double) object_height/floor_height;
    //int y_floor_position = int (y_floor_proportion * floor_height);
    //int screen_position = floor_starting_point + object_height;
    //int centered_screen_pos = screen_position - object_height;
    return floor_starting_point + ((floor_height - object_height)/floor_height)*floor_height;
}

int ObjectDrawer::findObjectHeight(double distance, DrawingInfo& drawing_info) {
    double object_wall_prop = (double) (drawing_info.object_height)/GRID_SIZE;
    double distance_prop = (double) GRID_SIZE/distance;
    double object_raw_height = object_wall_prop * distance_prop * 255;
    //int object_screen_height = (int) (height_prop*object_raw_height);
    return (int) object_raw_height;
}

int ObjectDrawer::findObjectWidth(double distance, DrawingInfo& drawing_info) {
    double object_width_prop = (double) drawing_info.object_width/GRID_SIZE;
    int wall_height_for_distance = (int) ((double) 100/distance * 188);
    double object_raw_width = object_width_prop*wall_height_for_distance;
    int object_screen_width = (int) (width_prop*object_raw_width);
    return object_screen_width;
}

void ObjectDrawer::getImageInformation(DrawingInfo& drawing_info) {
    int vector_pos = drawing_info.object_type;
    ImageInfo image_info = image_info_vector[vector_pos];
    drawing_info.object_width =  (int) (image_info.object_width*GRID_SIZE);
    drawing_info.object_height = (int) (image_info.object_height*GRID_SIZE);
    drawing_info.image_width = image_info.image_width;
    drawing_info.image_height = image_info.image_height;
    drawing_info.texture_name = image_info.image_path;
    drawing_info.object_name = image_info.object_name;
}

int ObjectDrawer::findRayNumberForAngle(double beta) {
    int counter = 0;
    while (true) {
        beta += 0.00327249;
        if (beta > 0.523599)
            break;
        ++counter;
    }
    return counter;
}

Area ObjectDrawer::assembleScreenArea(int ray_no, DrawingInfo& drawing_info) {
    int width_factor = window_width/PROJECTION_PLANE_width;
    int distance = (int) drawing_info.hit_distance;
    int col_height = findColumnHeight(distance);
    int col_starting_point = findColumnStartingPoint(col_height);
    Area screen_area(
            ray_no*width_factor,col_starting_point, width_factor, col_height
    );
    //printf("Rayo %d:Se coloca una pared a distancia %d, en (%d, %d), con un ancho de %d y altura de %d\n",
    //ray_no, distance, ray_no*width_factor, col_starting_point, width_factor, col_height);
    return screen_area;
}

int ObjectDrawer::findColumnHeight(int distance) {
    auto height_proportion = (double) GRID_SIZE/distance;
    return (int) (height_proportion*255);
}


int ObjectDrawer::findColumnStartingPoint(int col_height) {
    return (window_height - col_height)/2;
}

Area ObjectDrawer::assembleScreenArea(DrawingInfo& drawing_info,
                                   double distance,
                                   double pl_ob_angle) {
    Area screen_area;
    findObjectProportions(drawing_info, distance, pl_ob_angle, screen_area);
    return screen_area;
}
