#ifndef BULLETS_H
#define BULLETS_H

#include "server/positionable.h"

class Bullets : public Positionable {
private:
    int bullets_given;
public:
    Bullets();
    ~Bullets();
};
#endif // BULLETS_H