#ifndef TREASURE_H
#define TREASURE_H

#include "server/positionable.h"

class Treasure : public Positionable {
protected:
    int points_given;

public:
    Treasure(int _points_given, std::string object_type);
    ~Treasure();
};


#endif // TREASURE_H