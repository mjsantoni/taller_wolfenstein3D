#ifndef TREASURE_H
#define TREASURE_H

#include "server/game/positionable.h"

class Treasure : public Positionable {
protected:
    int points_given;

public:
    Treasure(std::string type, int id, int _points_given);
    ~Treasure();

    Treasure(const Treasure& other);
    Treasure& operator=(const Treasure& other);


    int getPoints();
};


#endif // TREASURE_H