#ifndef KEY_H
#define KEY_H

#include "server/game/positionable.h"

class Key : public Positionable {
private:
    
public:
    Key(int id);
    //pickUp() // unlocks
    ~Key();
};


#endif // KEY_H