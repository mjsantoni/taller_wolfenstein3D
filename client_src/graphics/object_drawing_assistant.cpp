//
// Created by andy on 10/2/21.
//

#include "client/graphics/object_drawing_assistant.h"

#define PROJECTION_PLANE_width 320
#define PROJECTION_PLANE_height 200
#define MAX_OBJECT_HEIGHT 300
#define ANCHO_TEXT 64

ObjectDrawingAssistant::ObjectDrawingAssistant(SdlWindow& _window,
                                             TextureManager& _texture_manager) :
                                             window(_window),
                                             texture_manager(_texture_manager) {
}

void ObjectDrawingAssistant::put3DObject(ObjectInfo& object_info,
                                         double pl_ob_angle) {
    int object_type = object_info.getObjectType();
    SDL_Texture* texture = texture_manager.getImageFromObjectType(object_type);
    Area image_area;
    if (object_info.isSprite()) {
        image_area = texture_manager.getAreaForEnemySprite(object_type,
                                            object_info.getSpriteAnimationNo());
        std::cout << "Se dibuja un enemigo " << object_info.getObjectName() << " con animacion " << object_info.getSpriteAnimationNo() << std::endl;
        std::cout << "Area del enemigo:\n";
        std::cout << "x: " << image_area.getX() << std::endl;
        std::cout << "y: " << image_area.getY() << std::endl;
        std::cout << "width: " << image_area.getWidth() << std::endl;
        std::cout << "height: " << image_area.getHeight() << std::endl;
    }
    else
        image_area = texture_manager.getImageAreaFromObjectType(object_type);
    image_area.setX((int) object_info.getHitGridPos() * image_area.getWidth());
    Area screen_area = assembleScreenArea(object_info, pl_ob_angle);
    window.loadImage(texture, image_area, screen_area);
    bool debug_object_drawing_info = false;
    if (!debug_object_drawing_info)
        return;
    std::cout << "Objeto: " << object_info.getObjectName() << std::endl;
    std::cout << "Animacion: " << object_info.getSpriteAnimationNo() << std::endl;
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
