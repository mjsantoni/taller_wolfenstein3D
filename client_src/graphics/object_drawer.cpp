//
// Created by andy on 4/12/20.
//

#include <SDL_image.h>
#include "client/object_drawer.h"
#include "client/sdl_exception.h"
#include "client/client_enemy.h"

void ObjectDrawer::setRenderer(SDL_Renderer* window_renderer,
                               int window_width,
                               int window_height) {
    renderer = window_renderer;
    this->window_width = window_width;
    this->window_height = window_height;
}

SDL_Texture* ObjectDrawer::drawImage(int ray_no, DrawingInfo& drawing_info,
                             Area& image_area) {

    std::string image_name = drawing_info.texture_name;
    switch (drawing_info.object_type) {
        case 1: {
            ClientWall_3d wall(image_name);
            return drawImage(wall, drawing_info, image_area);
        }
        case 2: {
            ClientEnemy enemy("enemy1", image_name);
            return drawImage(enemy, drawing_info, image_area);
        }
    }
    //printf("Se copiara una pared desde: (%d, %d) con ancho de %d y altura de %d\n", image_area.getX(), image_area.getY(), image_area.getWidth(), image_area.getHeight());
}

SDL_Texture* ObjectDrawer::drawImage(ClientWall_3d wall,
                                    DrawingInfo& drawing_info,
                                    Area& image_area) {
    SdlTexture sdl_texture(wall.getTextureName());
    SDL_Texture* image = sdl_texture.loadTexture(renderer, image_area);
    image_area.setX((int) (drawing_info.hit_grid_pos*image_area.getWidth()));
    image_area.setWidth(image_area.getWidth()/64);
    return image;
}

SDL_Texture* ObjectDrawer::drawImage(ClientEnemy enemy,
                                     DrawingInfo& drawing_info,
                                     Area& image_area) {
    SdlTexture sdl_texture(enemy.getTextureName());
    SDL_Texture* image = sdl_texture.loadTexture(renderer, image_area);
    //image_area.setWidth(2);
    return image;
}
