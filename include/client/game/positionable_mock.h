//
// Created by andy on 11/12/20.
//

#ifndef TP_WOLFENSTEIN_POSITIONABLE_MOCK_H
#define TP_WOLFENSTEIN_POSITIONABLE_MOCK_H

#include <SDL_render.h>
#include <string>

class PositionableMock {
public:
    PositionableMock(std::string object_name, int object_type, bool is_sprite,
                     std::string image_name, int object_width, int object_height);
    PositionableMock(std::string object_name, int object_type, bool is_sprite,
                     std::string image_name, std::string unique_name,
                     int object_width, int object_height);
    int getObjectType();
    bool isSprite();
    int getCurrentImageNumber();
    std::string getTextureName();
    void setPosition(int x_pos, int y_pos);
    std::pair<int, int> getPosition();
    int getWidth();
    int getHeight();

    virtual std::string getObjectName();

protected:
    std::string object_name;
    int object_type;
    bool is_sprite;
    int sprite_image_number = 0;
    std::string texture_name;
    std::string unique_name;
    std::pair<int, int> position;
    int object_width;
    int object_height;
};


#endif //TP_WOLFENSTEIN_POSITIONABLE_MOCK_H
