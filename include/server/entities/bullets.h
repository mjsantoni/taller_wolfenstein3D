#ifndef BULLETS_H
#define BULLETS_H

#include "server/game/positionable.h"

class Bullets : public Positionable {
private:
    int bullets_given;

public:
    Bullets(std::string id, int _bullets_given);
    ~Bullets();
};
#endif // BULLETS_H