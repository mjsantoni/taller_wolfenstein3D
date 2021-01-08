#ifndef HP_ITEM_H
#define HP_ITEM_H

#include "server/game/positionable.h"

class HPItem : public Positionable {
protected:
    int hp_given;
    
public:
    HPItem(std::string type, std::string id, int _hp_given);
    ~HPItem();

    int getHP();
};

#endif // HP_ITEM_H