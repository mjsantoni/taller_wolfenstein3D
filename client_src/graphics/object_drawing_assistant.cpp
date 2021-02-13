//
// Created by andy on 10/2/21.
//

#include "client/graphics/object_drawing_assistant.h"

#define PROJECTION_PLANE_width 320
#define PROJECTION_PLANE_height 200
#define MAX_OBJECT_HEIGHT 300
#define ANCHO_TEXT 64

ObjectDrawingAssistant::ObjectDrawingAssistant(SdlWindow& _window) :
                                               window(_window) {
}

void ObjectDrawingAssistant::put3DObject(ObjectInfo& object_info,
                                         double pl_ob_angle) {
    Area image_area;
    SDL_Texture* image = getObjectImage(object_info, image_area);
    image_area.setX((int) object_info.getHitGridPos() * image_area.getWidth());
    Area screen_area = assembleScreenArea(object_info, pl_ob_angle);
    window.loadImage(image, image_area, screen_area);
    SDL_DestroyTexture(image);
    bool debug_object_drawing_info = false;
    if (!debug_object_drawing_info)
        return;
    printf("Nombre de objeto: %s\n", object_info.getObjectName().c_str());
    printf("Distancia: %f\n", object_info.getHitDistance());
    printf("Pos x: %d\n", screen_area.getX());
    printf("Pos y: %d\n", screen_area.getY());
    printf("Altura: %d\n", screen_area.getHeight());
    printf("Ancho: %d\n", screen_area.getWidth());
    printf("Ancho de pantalla: %d\n", window_width);
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
    double object_height = findObjectHeight(distance);
    int y0 = findY0(object_height);
    double y1 = y0 + object_height;
    auto col_height = double(y0 - y1);
    double x0 = tan(pl_ob_angle) * VIEW_DIST;
    double object_width = col_height;
    double x = (SCREEN_WIDTH/2 + x0 - object_width/2);
    Area area(x, y1, object_width, col_height);
    return area;
}

double ObjectDrawingAssistant::findObjectHeight(double distance) {
    auto height_proportion = (double) OBJECT_HEIGHT/distance;
    return (height_proportion*proj_plane_distance); // altura muro
}

int ObjectDrawingAssistant::findY0(double object_height) {
    return (int (SCREEN_HEIGHT/2) - int (object_height/2));
}

Area ObjectDrawingAssistant::assembleScreenArea(ObjectInfo& object_info,
                                          double pl_ob_angle) {
    Area screen_area =
            findObjectProportions(object_info, pl_ob_angle);
    return screen_area;
}

void ObjectDrawingAssistant::setDimensions(int width, int height) {
    window_width = width;
    window_height = height;
    width_factor = width/320;
    height_factor = (int) (height/(0.8*200));
}
