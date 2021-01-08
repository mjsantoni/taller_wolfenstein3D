#ifndef GUN_H
#define GUN_H

#include "server/game/positionable.h"

class Gun : public Positionable {
protected:
    int damage;
    int bullets_per_spray;
    double fire_rate;
    double precision;

public:
    Gun(std::string type, int id, int _bullets_per_spray, double _fire_rate,
        double _precision);

    ~Gun();
};

#endif // GUN_H