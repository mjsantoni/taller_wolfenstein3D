//
// Created by andy on 1/12/20.
//

#ifndef TP_WOLFENSTEIN_DRAWINGINFO_H
#define TP_WOLFENSTEIN_DRAWINGINFO_H


#include "../Game/Positionable.h"

class DrawingInfo {
public:
    int object_x_pos;
    int object_y_pos;
    int object_type;
    double object_distance;
    int object_image_height;
    double object_image_width;
    int object_side;
    double hit_distance;
    int hit_x;
    int hit_y;
};


#endif //TP_WOLFENSTEIN_DRAWINGINFO_H
