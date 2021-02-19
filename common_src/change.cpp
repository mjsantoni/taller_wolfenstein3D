#include "common/change.h"

Change::Change(int _change_id, int _id, int _value1, int _value2, bool _is_global) :
        change_id(_change_id),
        id(_id),
        value1(_value1),
        value2(_value2),
        is_global(_is_global) {}

Change::Change(int _change_id, int _id, int _value1, int _value2) :
        change_id(_change_id),
        id(_id),
        value1(_value1),
        value2(_value2),
        is_global(true) {}

Change::Change() : change_id(INVALID),
           id(INVALID),
           value1(INVALID),
           value2(INVALID),
           is_global(false) {}

bool Change::isInvalid() const { return change_id == INVALID; }

int Change::getChangeID() const { return change_id; }

int Change::getPlayerID() const { return id; }

int Change::getFirstValue() const { return value1; }

int Change::getSecondValue() const { return value2; }

bool Change::isGlobal() const { return is_global; }

std::string Change::serialize() {
    std::ostringstream string;
    string << change_id << "/" << id << "/" << value1 << "/" << value2;
    return string.str();
}
