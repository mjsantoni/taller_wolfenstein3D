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
    SdlTexture* texture = texture_manager.getTextureFromObjectType(object_type);
    Area image_area;
    Area screen_area = assembleScreenArea(object_info, pl_ob_angle);
    if (object_info.isSprite()) {
        std::cout << "sprite no: " << object_info.getSpriteAnimationNo() << std::endl;
        int sprite_no = object_info.getSpriteAnimationNo();
        auto* sprite = (SdlSprite*) texture;
        sprite -> render(screen_area, sprite_no);
        return;
    }
    image_area = texture_manager.getImageAreaFromObjectType(object_type);
    image_area.setX((int)object_info.getHitGridPos()*image_area.getWidth());
    texture -> render(image_area, screen_area);
}

Area ObjectDrawingAssistant::findObjectProportions(ObjectInfo& object_info,
                                             double pl_ob_angle) {
    double distance = object_info.getHitDistance();
    distance *= cos(pl_ob_angle);
    double object_height = findObjectHeight(distance);
    int object_y_starting_point = findObjectStartingPoint(object_height);
    double screen_starting_point = object_y_starting_point + object_height;
    auto col_height = double(object_y_starting_point - screen_starting_point);
    double object_x_starting_point = tan(pl_ob_angle) * VIEW_DIST;
    double object_width = col_height;
            //col_height * (SCREEN_DRAWING_WIDTH/SCREEN_DRAWING_HEIGHT);
    double screen_x_starting_point = ((double) SCREEN_DRAWING_WIDTH/2 +
                                    object_x_starting_point - object_width / 2);
    //std::cout << "Scr start point: " << screen_starting_point << std::endl;
    //std::cout << "Col height: " << col_height << std::endl;
    //std::cout << "Scr total height " << SCREEN_DRAWING_HEIGHT << std::endl;
    //col_height = (screen_starting_point + col_height) > SCREEN_DRAWING_HEIGHT ?
            //SCREEN_DRAWING_HEIGHT - screen_starting_point: col_height;
    Area area((int) screen_x_starting_point, (int) screen_starting_point,
              (int) object_width, col_height);
    return area;
}

double ObjectDrawingAssistant::findObjectHeight(double distance) {
    auto height_proportion = (double) OBJECT_HEIGHT/distance;
    return (height_proportion*proj_plane_distance); // altura muro
}

int ObjectDrawingAssistant::findObjectStartingPoint(double object_height) {
    return (int (SCREEN_DRAWING_HEIGHT/2) - int (object_height/2));
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
    width_factor = width/SCREEN_DRAWING_WIDTH;
    height_factor = height/SCREEN_DRAWING_HEIGHT;
}
