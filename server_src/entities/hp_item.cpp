#include "server/entities/hp_item.h"

HPItem::HPItem(std::string type, int id, int _hp_given) :
               Positionable("hp_item", type, id, false),
               hp_given(_hp_given) {
}

int HPItem::getHP() {
    return hp_given;
}

HPItem::HPItem(const HPItem& other) {
    this->category = other.category;
    this->type = other.type;
    this->id = other.id;
    this->is_blocking = other.is_blocking;
    this->hp_given = other.hp_given;
}

HPItem& HPItem::operator=(const HPItem& other) {
    this->category = other.category;
    this->type = other.type;
    this->id = other.id;
    this->is_blocking = other.is_blocking;
    this->hp_given = other.hp_given;
    return *this;
}

HPItem::~HPItem() {}
