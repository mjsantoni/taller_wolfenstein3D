#ifndef TP_WOLFENSTEIN_CHANGE_H
#define TP_WOLFENSTEIN_CHANGE_H

#include "common/changes.h"

class Change {
private:
    int change_id;
    int player_id;
    int value1;
    int value2;
    bool is_global;

public:
    Change(int _change_id, int _player_id, int _value1, int _value2, bool _is_global) :
                change_id(_change_id),
                player_id(_player_id),
                value1(_value1),
                value2(_value2),
                is_global(_is_global) {}

    int getChangeID() const { return change_id; }
    int getPlayerID() const { return player_id; }
    int getFirstValue() const { return value1; }
    int getSecondValue() const { return value2; }
    bool isGlobal() const { return is_global; }
};


#endif //TP_WOLFENSTEIN_CHANGE_H
