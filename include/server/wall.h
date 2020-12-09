#ifndef WALL_H
#define WALL_H

#include "positionable.h"

class Wall : public Positionable {
private:

public:
    Wall(std::string object_type);
    ~Wall();
};


#endif // WALL_H