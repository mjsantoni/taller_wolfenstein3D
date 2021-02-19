//
// Created by andy on 10/2/21.
//

#include "client/graphics/object_drawing_assistant.h"

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
    double object_x_starting_point = tan(pl_ob_angle) * view_dist;
    double object_width = col_height;
    double screen_x_starting_point = ((double) screen_width/2 +
                                    object_x_starting_point - object_width / 2);
    //col_height = (screen_starting_point + col_height) > SCREEN_DRAWING_HEIGHT ?
            //SCREEN_DRAWING_HEIGHT - screen_starting_point: col_height;
    Area area((int) screen_x_starting_point, (int) screen_starting_point,
              (int) object_width, col_height);
    return area;
}

double ObjectDrawingAssistant::findObjectHeight(double distance) {
    auto height_proportion = (double) OBJECT_HEIGHT/distance;
    return (height_proportion*proj_plane_distance);
}

int ObjectDrawingAssistant::findObjectStartingPoint(double object_height) {
    return (int (screen_height/2) - int (object_height/2));
}

Area ObjectDrawingAssistant::assembleScreenArea(ObjectInfo& object_info,
                                          double pl_ob_angle) {
    Area screen_area =
            findObjectProportions(object_info, pl_ob_angle);
    return screen_area;
}

void ObjectDrawingAssistant::setDimensions(int width, int height) {
    screen_width = width;
    screen_height = height;
    view_dist = (screen_width > screen_height) ? screen_width : screen_height;
    width_factor = width/screen_width;
    height_factor = height/screen_height;
    proj_plane_distance = (int) (((double) screen_width/2) / tan(FOV/2));
}
