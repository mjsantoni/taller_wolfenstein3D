#ifndef TP_WOLFENSTEIN_EVENT_FACTORY_H
#define TP_WOLFENSTEIN_EVENT_FACTORY_H

#include "common/shared_queue.h"
#include "common/event.h"

class EventFactory {
 private:
  SharedQueue<Event>& eventQueue;

 public:
  /* Constructor de la clase que desserializa los eventos y pushea a la cola de eventos. */
  explicit EventFactory(SharedQueue<Event>& _event_queue);

  void createAndPushFromBytes(char* bytes);
};

#endif //TP_WOLFENSTEIN_EVENT_FACTORY_H
