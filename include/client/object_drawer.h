//
// Created by andy on 4/12/20.
//

#ifndef TP_WOLFENSTEIN_OBJECTDRAWER_H
#define TP_WOLFENSTEIN_OBJECTDRAWER_H


#include <SDL_render.h>
#include "drawing_info.h"
#include "client_wall_3d.h"
#include "client_enemy.h"

class ObjectDrawer {
public:
    void setRenderer(SDL_Renderer* window_renderer, int window_width,
                     int window_height);
    SDL_Texture* drawImage(int ray_no, DrawingInfo& drawing_info,
                           Area& image_area);
    SDL_Texture* drawImage(ClientWall_3d wall, DrawingInfo& drawing_info,
                           Area& image_area);
    SDL_Texture* drawImage(ClientEnemy enemy, DrawingInfo& drawing_info,
                                         Area& image_area);
private:
    SDL_Renderer* renderer;
    int window_width;
    int window_height;
};


#endif //TP_WOLFENSTEIN_OBJECTDRAWER_H
