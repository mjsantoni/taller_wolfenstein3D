#ifndef WALL_H
#define WALL_H

#include "server/game/positionable.h"

class Wall : public Positionable {
private:
    bool is_fake;
public:
    Wall(std::string _wall_type, int id, bool _is_fake);

    Wall(const Wall& other);
    Wall& operator=(const Wall& other);

    ~Wall();
};


#endif // WALL_H