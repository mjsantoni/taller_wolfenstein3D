//
// Created by andy on 2/12/20.
//

#ifndef TP_WOLFENSTEIN_RAYINFO_H
#define TP_WOLFENSTEIN_RAYINFO_H

#include <utility>

class RayInfo {
private:
    int object_type;
    double hit_distance;
    double hit_grid_position;
    std::pair<int, int> map_starting_position;
public:
    int getObjectType() const;
    void setObjectType(int objectType);
    double getHitDistance() const;
    void setHitDistance(double hitDistance);
    double getHitGridPosition() const;
    void setHitGridPosition(double hitGridPosition);
    std::pair<int, int> getMapStartingPosition() const;
    void setMapStartingPosition(std::pair<int, int> _map_starting_position);
};

#endif //TP_WOLFENSTEIN_RAYINFO_H
