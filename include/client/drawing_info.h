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
    double object_height;
    double object_width;
    int object_side;
    double hit_distance;
    double hit_grid_pos;
    int hit_x;
    int hit_y;
    bool is_sprite;
    int sprite_image_number;
    std::string texture_name;
    std::string object_name;
    int sprite_number = 0;
    int sprite_rows;
    int sprite_cols;
    int sprite_h_padding;
    int sprite_v_padding;
};

#endif //TP_WOLFENSTEIN_DRAWINGINFO_H
