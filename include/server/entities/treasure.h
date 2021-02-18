#ifndef TREASURE_H
#define TREASURE_H

#include "server/game/positionable.h"

class Treasure : public Positionable {
protected:
    int points_given;

public:
    Treasure(std::string type, int id, int _points_given);

    int getPoints();

    ~Treasure();
};

#endif // TREASURE_H