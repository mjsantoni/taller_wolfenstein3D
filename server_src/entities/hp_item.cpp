#include "server/hp_item.h"

HPItem::HPItem(int _hp_given, std::string id) :
               Positionable("hp_item", id, false),
               hp_given(_hp_given) {
}

int HPItem::getHP() {
    return hp_given;
}
HPItem::~HPItem()
{
}