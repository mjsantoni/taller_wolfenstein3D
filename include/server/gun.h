#ifndef GUN_H
#define GUN_H

#include "server/positionable.h"

class Gun : public Positionable {
protected:
    int damage;
    int bullets_per_spray;
    double fire_rate;
    double precision;

public:
    Gun(int _bullets_per_spray, double _fire_rate, 
        double _precision, std::string id);

    ~Gun();
};

#endif // GUN_H