#include "server/event_queue.h"

EventQueue::EventQueue() : is_closed(false) {}

void EventQueue::push(Event event) {
    events.push(event);
}

Event EventQueue::pop() {
    Event event = events.front();
    events.pop();
    return event;
}