//
// Created by andy on 26/11/20.
//

#include "client/graphics/area.h"

Area::Area(int x, int y, int width, int height) :
        x(x), y(y), width(width), height(height){
}

Area::Area() : x(0), y(0), width(0), height(0) {}

int Area::getX() const {
    return x;
}

int Area::getY() const {
    return y;
}

int Area::getWidth() const {
    return width;
}

int Area::getHeight() const {
    return height;
}

void Area::setX(int new_x) {
    x = new_x;
}

void Area::setY(int new_y) {
    y = new_y;
}

void Area::setWidth(int new_width) {
    width = new_width;
}

void Area::setHeight(int new_height) {
    height = new_height;
}


