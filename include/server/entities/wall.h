#ifndef WALL_H
#define WALL_H

#include "server/game/positionable.h"

class Wall : public Positionable {
private:
    bool is_fake;
public:
    Wall(std::string _wall_type, bool _is_fake);
    ~Wall();
};


#endif // WALL_H