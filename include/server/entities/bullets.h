#ifndef BULLETS_H
#define BULLETS_H

#include "positionable.h"

class Bullets : public Positionable {
private:
    int bullets_given;

public:
    Bullets(int id, int _bullets_given, std::string type);

    ~Bullets();
};
#endif // BULLETS_H