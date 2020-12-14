#include "server/event_handler.h"

EventHandler::EventHandler(EventQueue& _eq) : eq(_eq) {}

int EventHandler::createAndPush(int i, int j, double a) {
    Event new_event(i,j,a);
    eq.push(new_event);
}