#include "server/hp_item.h"


HPItem::HPItem(int _hp_given, std::string object_type) :
               Positionable(object_type, "path", 1, false), hp_given(_hp_given) {
}

HPItem::~HPItem()
{
}