//
// Created by andy on 1/12/20.
//

#ifndef TP_WOLFENSTEIN_DRAWINGINFO_H
#define TP_WOLFENSTEIN_DRAWINGINFO_H


#include "positionable_mock.h"

class DrawingInfo {
public:
    int object_x_pos;
    int object_y_pos;
    int object_type;
    int image_height;
    int image_width;
    int object_height;
    int object_width;
    int object_side;
    double hit_distance;
    double hit_grid_pos;
    int hit_x;
    int hit_y;
    bool is_sprite;
    int sprite_image_number;
    std::string texture_name;
};


#endif //TP_WOLFENSTEIN_DRAWINGINFO_H
