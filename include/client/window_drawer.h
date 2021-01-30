//
// Created by andy on 23/1/21.
//

#ifndef TP_WOLFENSTEIN_WINDOW_DRAWER_H
#define TP_WOLFENSTEIN_WINDOW_DRAWER_H


#include <SDL_render.h>
#include "object_info.h"
#include "client/graphics/area.h"
#include "client/graphics/sdl_texture.h"
#include "client/graphics/sdl_sprite.h"
#include <map>

class WindowDrawer {
private:
    int window_width;
    int window_height;
    int map_grid_size;
    std::map<int, std::pair<int, int>> floor_info;
    SDL_Renderer* renderer;
public:
    SDL_Texture* drawWall(ObjectInfo& drawing_info, Area& image_area);
    void putTextureAt(SDL_Texture* texture, Area src, Area dest);
    SDL_Texture* drawImage(ObjectInfo& object_info, Area& image_area);
};


#endif //TP_WOLFENSTEIN_WINDOW_DRAWER_H
