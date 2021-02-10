//
// Created by andy on 10/2/21.
//

#include "drawing_assistant.h"

#define PROJECTION_PLANE_width 320
#define PROJECTION_PLANE_height 200
#define MAX_OBJECT_HEIGHT 300

DrawingAssistant::DrawingAssistant(SdlWindow& _window,
                                std::map<int, std::pair<int, int>>& _floor_info,
                                int _map_grid_size) :
                                window(_window),
                                floor_info(_floor_info),
                                map_grid_size(_map_grid_size) {
    setDimensions(window.getWidth(), window.getHeight());
}

void DrawingAssistant::drawFloor(int x_pos, int wall_posY, int wall_height) {
    int fsp_for_column = wall_posY + wall_height;
    int fh_for_column = window_height - fsp_for_column;
    std::pair<int, int> ray_floor_info {fsp_for_column, fh_for_column};
    floor_info.insert(std::pair<int,std::pair<int,int>>(x_pos, ray_floor_info));
    Area area(x_pos*width_factor, fsp_for_column, width_factor, fh_for_column);
    window.drawRectangle(area, 123, 123, 123, 0);
}

void DrawingAssistant::drawCeiling(int x_pos, int y_pos) {
    Area area(x_pos*width_factor, 0, width_factor, y_pos);
    window.drawRectangle(area, 60, 60, 60, 0);
}

void DrawingAssistant::setDimensions(int width, int height) {
    window_width = width;
    window_height = height;
    width_factor = width / 320;
    height_factor = (int) (height / (0.8 * 200));
}

int DrawingAssistant::findColumnHeight(int distance) {
    auto height_proportion = (double) map_grid_size/distance;
    return (int) (height_proportion*255);
}

int DrawingAssistant::findColumnStartingPoint(int col_height) {
    return (window_height - col_height)/2;
}

void DrawingAssistant::putWall(int ray_no, ObjectInfo& object_info) {
    Area image_area;
    SDL_Texture* texture = loadWallTexture(object_info, image_area);
    Area screen_area = assembleScreenArea(ray_no, object_info);
    window.loadImage(texture, image_area, screen_area);
    SDL_DestroyTexture(texture);
}

SDL_Texture* DrawingAssistant::loadWallTexture(ObjectInfo& object_info,
                                               Area& image_area) {
    SdlTexture sdl_texture(object_info.getImagePath());
    SDL_Texture* image = sdl_texture.loadTexture(window.getRenderer(),
                                                 image_area);
    image_area.setX((int) (object_info.getHitGridPos() *image_area.getWidth()));
    image_area.setWidth(image_area.getWidth()/map_grid_size);
    return image;
}

Area DrawingAssistant::assembleScreenArea(int ray_no, ObjectInfo& object_info) {
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

void DrawingAssistant::putFloorAndCeiling(int ray_no, ObjectInfo& object_info) {
    Area screen_area = assembleScreenArea(ray_no, object_info);
    drawFloor(ray_no, screen_area.getY(), screen_area.getHeight());
    drawCeiling(ray_no, screen_area.getY());
}
