//
// Created by andy on 10/12/20.
//

#ifndef TP_WOLFENSTEIN_DRAWABLE_H
#define TP_WOLFENSTEIN_DRAWABLE_H


#include <utility>

class Drawable {
private:
    int object_type;
    int sprite_animation_no;
    std::pair<int, int> map_position;
public:
    explicit Drawable(int _object_type);
    Drawable(int _object_type, int _sprite_animation_no);
    int getObjectType();
    std::pair<int, int> getMapPosition();
    void setMapPosition(int x_pos, int y_pos);
};


#endif //TP_WOLFENSTEIN_DRAWABLE_H
