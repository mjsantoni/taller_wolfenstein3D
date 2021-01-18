#ifndef HP_ITEM_H
#define HP_ITEM_H

#include "server/game/positionable.h"

class HPItem : public Positionable {
protected:
    int hp_given;
    
public:
    HPItem(std::string type, int id, int _hp_given);
    ~HPItem();

    HPItem(const HPItem& other);
    HPItem& operator=(const HPItem& other);

    int getHP();
};

#endif // HP_ITEM_H