#ifndef WALL_H
#define WALL_H

#include "positionable.h"

class Wall : public Positionable {

public:
    Wall(std::string _wall_type, int id);
    ~Wall();
};


#endif // WALL_H