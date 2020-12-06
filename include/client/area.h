//
// Created by andy on 26/11/20.
//

#ifndef TP_WOLFENSTEIN_AREA_H
#define TP_WOLFENSTEIN_AREA_H


class Area {
public:
    Area(int x, int y, int width, int height);
    Area();
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    void setX(int new_x);
    void setY(int new_y);
    void setWidth(int new_width);
    void setHeight(int new_height);
private:
    int x;
    int y;
    int width;
    int height;
};


#endif //TP_WOLFENSTEIN_AREA_H
