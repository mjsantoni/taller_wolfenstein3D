//
// Created by andy on 4/12/20.
//

#ifndef TP_WOLFENSTEIN_OBJECTDRAWER_H
#define TP_WOLFENSTEIN_OBJECTDRAWER_H


#include <SDL_render.h>
#include "DrawingInfo.h"
#include "Wall_3d.h"
#include "Enemy.h"

class ObjectDrawer {
public:
    void setRenderer(SDL_Renderer* window_renderer, int window_width,
                     int window_height);
    SDL_Texture* drawImage(int ray_no, DrawingInfo& drawing_info,
                           Area& image_area);
    SDL_Texture* drawImage(Wall_3d wall, DrawingInfo& drawing_info,
                           Area& image_area);
    SDL_Texture* drawImage(Enemy enemy, DrawingInfo& drawing_info,
                                         Area& image_area);
private:
    SDL_Renderer* renderer;
    int window_width;
    int window_height;
};


#endif //TP_WOLFENSTEIN_OBJECTDRAWER_H
