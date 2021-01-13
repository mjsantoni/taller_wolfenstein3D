#ifndef TP_WOLFENSTEIN_EVENT_H
#define TP_WOLFENSTEIN_EVENT_H

#include "common/events.h"

class Event {
private:
    int event_id;
    int player_id;
    int value;
public:
    Event(int _event_id,int _player_id, int _value) :
            player_id(_player_id),
            event_id(_event_id),
            value(_value) {}

    int getEventID() {return event_id;}
    int getPlayerID() {return player_id;}
    int getValue() {return value;}
};

#endif //TP_WOLFENSTEIN_EVENT_H
