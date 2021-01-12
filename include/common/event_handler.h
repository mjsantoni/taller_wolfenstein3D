#ifndef TP_WOLFENSTEIN_EVENT_HANDLER_H
#define TP_WOLFENSTEIN_EVENT_HANDLER_H

#include "event_queue.h"

class EventHandler {
private:
    EventQueue& eq;
public:
    EventHandler(EventQueue& _eq);
    Event createAndPush(int i, int j, double a);
};


#endif //TP_WOLFENSTEIN_EVENT_HANDLER_H
