#ifndef TP_WOLFENSTEIN_EVENT_H
#define TP_WOLFENSTEIN_EVENT_H

#include "common/events.h"

class Event {
private:
    int event_id;
    int player_id;
    int value;
public:
    Event(int _player_id, int _event_id, int _value);
};

#endif //TP_WOLFENSTEIN_EVENT_H
