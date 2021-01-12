#ifndef TP_WOLFENSTEIN_EVENTS_QUEUE_H
#define TP_WOLFENSTEIN_EVENTS_QUEUE_H

#include <queue>
#include <mutex>
#include "event.h"

class EventQueue {
private:
    bool is_closed;
    std::mutex m;
    std::queue<Event> events;

public:
    explicit EventQueue();
    void push(Event event);
    Event pop();
    ~EventQueue();
};

#endif //TP_WOLFENSTEIN_EVENTS_QUEUE_H
