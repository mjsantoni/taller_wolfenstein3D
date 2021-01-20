#ifndef TP_WOLFENSTEIN_EVENT_H
#define TP_WOLFENSTEIN_EVENT_H

#include "common/events.h"

class Event {
public:
    int event_id;
    int player_id;
    int value;
    Event(int _event_id,int _player_id, int _value) :
            player_id(_player_id),
            event_id(_event_id),
            value(_value) {}

    int getEventID() const { return event_id; }
    int getPlayerID() const { return player_id; }
    int getValue() const { return value; }
};

#endif //TP_WOLFENSTEIN_EVENT_H
