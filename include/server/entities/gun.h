#ifndef GUN_H
#define GUN_H

#include "server/game/positionable.h"

class Gun : public Positionable {
protected:
    int bullets_per_spray;
    double fire_rate;
    double precision;
    int range;

public:
    Gun();
    Gun(std::string type, int id, int _bullets_per_spray,
        double _fire_rate, double _precision, int _range);

    int getDamage();
    int getRange();
    double getPrecision();
    int getBulletsPerSpray();

    ~Gun();

    Gun(const Gun& other);
    Gun& operator=(const Gun& other);

};

#endif // GUN_H
