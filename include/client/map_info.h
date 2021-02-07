//
// Created by andy on 1/12/20.
//

#ifndef TP_WOLFENSTEIN_DRAWINGINFO_H
#define TP_WOLFENSTEIN_DRAWINGINFO_H

#include <utility>

class MapInfo {
public:
    double object_width;
    double object_height;
    int object_side;
    double hit_distance;
    double hit_grid_pos;
    std::pair<int, int> map_starting_pos;

    std::pair<int, int> getMapStartingPos() const;
    void setMapStartingPos(std::pair<int, int> _map_starting_pos);
    double getObjectWidth() const;
    void setObjectWidth(double _object_width);
    double getObjectHeight() const;
    void setObjectHeight(double _object_height);
    int getObjectSide() const;
    void setObjectSide(int objectSide);
    double getHitDistance() const;
    void setHitDistance(double hitDistance);
    double getHitGridPos() const;
    void setHitGridPos(double hitGridPos);
};

#endif //TP_WOLFENSTEIN_DRAWINGINFO_H
