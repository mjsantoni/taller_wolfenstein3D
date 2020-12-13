//
// Created by andy on 4/12/20.
//

#ifndef TP_WOLFENSTEIN_OBJECTDRAWER_H
#define TP_WOLFENSTEIN_OBJECTDRAWER_H


#include <SDL_render.h>
#include <vector>
#include "drawing_info.h"
#include "client_wall.h"
#include "image_parser.h"
#include "image_info.h"

class ObjectDrawer {
public:
    ObjectDrawer();
    void setRenderer(SDL_Renderer* window_renderer, int window_width,
                     int window_height);
    SDL_Texture* drawImage(DrawingInfo& drawing_info, Area& image_area);
    void drawFloor(int x_pos, int wall_posY, int wall_height);
    void drawCeiling(int x_pos, int y_pos);
    void findObjectProportions(DrawingInfo& drawing_info, double distance,
                               int max_dist_x, int max_dist_y, double beta, Area& screen_area);
    void getImageInformation(DrawingInfo& drawing_info);
    SDL_Texture* drawWall(DrawingInfo& drawing_info, Area& image_area);
private:
    SDL_Renderer* renderer;
    int window_width;
    int window_height;
    int floor_starting_point;
    int floor_height;
    std::vector<ImageInfo> image_info_vector;
    ImageParser image_parser;
};


#endif //TP_WOLFENSTEIN_OBJECTDRAWER_H