#ifndef GUN_H
#define GUN_H

#include "server/game/positionable.h"

class Gun : public Positionable {
protected:
    int damage = 20;
    int bullets_per_spray;
    double fire_rate;
    double precision;

public:
    Gun(std::string type, int id, int _bullets_per_spray, double _fire_rate,
        double _precision);

    int getDamage();
    int getRange();

    ~Gun();

};

#endif // GUN_H