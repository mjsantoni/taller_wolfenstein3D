#include "common/event_factory.h"

#include <string>

#define EVENT_ID 0
#define PLAYER_ID 1
#define VALUE 2

EventFactory::EventFactory(SharedQueue<Event> &_event_queue) :
                                    eventQueue(_event_queue) {}

void EventFactory::createAndPushFromBytes(char* bytes) {
    std::vector<int> buffer;
    std::stringstream ss(bytes);
    std::string s;
    while (std::getline(ss, s, '/')) {
        if (s.size() == 0) continue;
        buffer.push_back(std::stoi(s));
    }
    Event event(buffer[EVENT_ID], buffer[PLAYER_ID], buffer[VALUE]);
    eventQueue.push(event);
}

/* test only */
void EventFactory::pushNewEvent(Event& event) {
    eventQueue.push(event);
}
