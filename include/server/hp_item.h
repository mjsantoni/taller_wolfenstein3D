#ifndef HP_ITEM_H
#define HP_ITEM_H

#include "server/positionable.h"

class HPItem : public Positionable {
protected:
    int hp_given;
    
public:
    HPItem(int _hp_given, std::string object_type);
    //giveHP()
    ~HPItem();
};

#endif // HP_ITEM_H