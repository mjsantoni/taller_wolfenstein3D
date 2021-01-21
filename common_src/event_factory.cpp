#include "common/event_factory.h"

EventFactory::EventFactory(SharedQueue<Event> &_event_queue) :
                                    eventQueue(_event_queue) {}

Event EventFactory::createAndPushFromInts(std::vector<int> event_ints) {
    Event new_event(event_ints[0], event_ints[1], event_ints[2]);
    eventQueue.push(new_event);
    return new_event;
}

Event EventFactory::createAndPushFromBytes(std::vector<uint8_t> bytes) {
    return createAndPushFromInts(convertToInts(bytes));
}

std::vector<int> EventFactory::convertToInts(std::vector<uint8_t> bytes) {
    return std::vector<int>(); // pendiente
}
