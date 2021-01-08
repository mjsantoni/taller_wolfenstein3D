#ifndef TREASURE_H
#define TREASURE_H

#include "server/game/positionable.h"

class Treasure : public Positionable {
protected:
    int points_given;

public:
    Treasure(std::string type, std::string id, int _points_given);
    ~Treasure();

    int getPoints();
};


#endif // TREASURE_H