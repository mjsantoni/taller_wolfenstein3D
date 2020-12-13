//
// Created by andy on 4/12/20.
//

#include <client/image_parser.h>
#include "client/object_drawer.h"

#define PROJECTION_PLANE_width 320
#define GRID_SIZE 64

ObjectDrawer::ObjectDrawer() {
    image_parser.fillImageVector(image_info_vector);
}

void ObjectDrawer::setRenderer(SDL_Renderer* window_renderer,
                               int window_width,
                               int window_height) {
    renderer = window_renderer;
    this->window_width = window_width;
    this->window_height = window_height;
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
    image_area.setWidth(image_area.getWidth()/64);
    return image;
    //printf("Se copiara una pared desde: (%d, %d) con ancho de %d y altura de %d\n", image_area.getX(), image_area.getY(), image_area.getWidth(), image_area.getHeight());
}

void ObjectDrawer::drawFloor(int x_pos, int wall_posY, int wall_height) {
    int width_factor = window_width/PROJECTION_PLANE_width;
    floor_starting_point = wall_posY + wall_height;
    floor_height = window_height - floor_starting_point;
    SDL_Rect floor_rect = {
            x_pos*width_factor, floor_starting_point, width_factor, floor_height
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
                                         int max_distance_x,
                                         int max_distance_y,
                                         double beta,
                                         Area& screen_area) {
    int delta_x = (int) (distance*sin(beta));
    double x_proportion = double (delta_x)/max_distance_x;
    int delta_y = (int) (distance*cos(beta));
    double y_proportion = double (delta_y)/max_distance_y;
    int x_pos = 160 + (int) (x_proportion*320);
    int y_pos = floor_height + (floor_height - (int) (y_proportion*floor_height));
    screen_area.setX(x_pos);
    screen_area.setY(y_pos);
    auto height_proportion = (double) drawing_info.object_height/distance;
    auto width_proportion = (double) drawing_info.object_width/distance;
    int height_projection = (int) (height_proportion*175);
    int width_projection = (int) (width_proportion*255);
    screen_area.setWidth(width_projection);
    screen_area.setHeight(height_projection);
}

void ObjectDrawer::getImageInformation(DrawingInfo& drawing_info) {
    int vector_pos = drawing_info.object_type;
    ImageInfo image_info = image_info_vector[vector_pos];
    drawing_info.object_width =  (int) (image_info.object_width*GRID_SIZE);
    drawing_info.object_height = (int) (image_info.object_height*GRID_SIZE);
    drawing_info.image_width = image_info.image_width;
    drawing_info.image_height = image_info.image_height;
    drawing_info.texture_name = image_info.image_path;
}
