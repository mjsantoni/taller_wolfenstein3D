#include "server/events/event_factory.h"
#include <string>

#define EVENT_ID 0
#define PLAYER_ID 1
#define VALUE 2
#define EVENT_SIZE 3

EventFactory::EventFactory(SharedQueue<Event>& _event_queue) :
    eventQueue(_event_queue) {}

void EventFactory::createAndPushFromBytes(char* bytes) {
  std::vector<int> buffer;
  std::stringstream ss(bytes);
  std::string s;
  while (std::getline(ss, s, '/')) {
    if (s.size() == 0) continue;
    buffer.push_back(std::stoi(s));
  }
  if (buffer.size() != EVENT_SIZE) return;
  Event event(buffer[EVENT_ID], buffer[PLAYER_ID], buffer[VALUE]);
  eventQueue.push(event);
}
