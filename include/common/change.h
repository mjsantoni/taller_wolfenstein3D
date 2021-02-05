#ifndef TP_WOLFENSTEIN_CHANGE_H
#define TP_WOLFENSTEIN_CHANGE_H

#include "common/changes.h"

#include <sstream>

class Change {
public:
    int change_id;
    int id;
    int value1;
    int value2;
    bool is_global;

    Change(int _change_id, int _id, int _value1, int _value2, bool _is_global) :
            change_id(_change_id),
            id(_id),
            value1(_value1),
            value2(_value2),
            is_global(_is_global) {}

    // Constructor para el lado del cliente
    Change(int _change_id, int _id, int _value1, int _value2) :
            change_id(_change_id),
            id(_id),
            value1(_value1),
            value2(_value2),
            is_global(true) {}

    Change() : change_id(INVALID),
               id(INVALID),
               value1(INVALID),
               value2(INVALID),
               is_global(false) {}

    bool isInvalid() const { return change_id == INVALID; }
    int getChangeID() const { return change_id; }
    int getPlayerID() const { return id; }
    int getFirstValue() const { return value1; }
    int getSecondValue() const { return value2; }
    bool isGlobal() const { return is_global; }

    std::string serialize() {
        std::ostringstream string;
        string << change_id << "/" << id << "/" << value1 << "/" << value2;
        return string.str();
    }
};

#endif //TP_WOLFENSTEIN_CHANGE_H
