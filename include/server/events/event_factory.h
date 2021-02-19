#ifndef TP_WOLFENSTEIN_EVENT_FACTORY_H
#define TP_WOLFENSTEIN_EVENT_FACTORY_H

#include "common/shared_queue.h"
#include "common/event.h"

class EventFactory {
private:
    SharedQueue<Event>& eventQueue;

public:
    explicit EventFactory(SharedQueue<Event>& _event_queue);

    void createAndPushFromBytes(char* bytes);

    void pushNewEvent(Event &event);
};

#endif //TP_WOLFENSTEIN_EVENT_FACTORY_H
