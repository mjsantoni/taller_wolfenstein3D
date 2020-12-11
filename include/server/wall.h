#ifndef WALL_H
#define WALL_H

#include "positionable.h"

class Wall : public Positionable {
private:
    std::string wall_type;
    bool is_fake;
public:
    Wall(std::string _wall_type, bool _is_fake);
    ~Wall();
};


#endif // WALL_H