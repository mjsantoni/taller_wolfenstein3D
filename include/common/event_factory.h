#ifndef TP_WOLFENSTEIN_EVENT_FACTORY_H
#define TP_WOLFENSTEIN_EVENT_FACTORY_H

#include "shared_queue.h"
#include "event.h"

class EventFactory {
private:
    SharedQueue<Event>& eventQueue;
    // Es de Event* o Event?

public:
    explicit EventFactory(SharedQueue<Event>& _event_queue);
    void createAndPushFromInts(std::vector<int> event_ints);

    std::vector<int> convertToInts(std::vector<uint8_t> bytes);

    Event createAndPushFromBytes(std::vector<uint8_t> bytes);

    void pushNewEvent(Event &event);
};


#endif //TP_WOLFENSTEIN_EVENT_FACTORY_H
