//
// Created by andy on 10/12/20.
//

#ifndef TP_WOLFENSTEIN_DRAWABLE_H
#define TP_WOLFENSTEIN_DRAWABLE_H


#include <utility>
#include <string>

class Drawable {
private:
    int object_type;
    std::string object_name;
    int sprite_animation_no;
    std::pair<int, int> map_position;
    int map_width;
public:
    explicit Drawable(int _object_type);
    Drawable(int _object_type, int _sprite_animation_no);
    int getObjectType();
    std::pair<int, int> getMapPosition();
    void setMapPosition(int x_pos, int y_pos);
    int getMapWidth();
    void setMapWidth(int width);
    std::string getObjectName();
    void setObjectName(std::string name);
};


#endif //TP_WOLFENSTEIN_DRAWABLE_H
