#include "server/entities/hp_item.h"

HPItem::HPItem(std::string type, int id, int _hp_given) :
               Positionable("hp_item", type, id, false),
               hp_given(_hp_given) {
}

int HPItem::getHP() {
    return hp_given;
}
HPItem::~HPItem() {}
