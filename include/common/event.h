#ifndef TP_WOLFENSTEIN_EVENT_H
#define TP_WOLFENSTEIN_EVENT_H

#include "common/events.h"
#include <sstream>

class Event {
 public:
  int event_id;
  int player_id;
  int value;

  /* Server-side constructor */
  Event(int _event_id, int _player_id, int _value);

  /* Invalid default constructor */
  Event();

  bool isInvalid() const;

  int getEventID() const;
  int getPlayerID() const;
  int getValue() const;

  /* Serializa sus valores a bytes para enviar */
  std::string serialize();
};

#endif //TP_WOLFENSTEIN_EVENT_H
