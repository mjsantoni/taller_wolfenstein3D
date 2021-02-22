#include "common/event.h"

Event::Event(int _event_id, int _player_id, int _value) :
    player_id(_player_id),
    event_id(_event_id),
    value(_value) {}

Event::Event() : event_id(INVALID),
                 player_id(INVALID),
                 value(INVALID) {}

bool Event::isInvalid() const { return event_id == INVALID; }

int Event::getEventID() const { return event_id; }

int Event::getPlayerID() const { return player_id; }

int Event::getValue() const { return value; }

std::string Event::serialize() {
  std::ostringstream string;
  string << event_id << "/" << player_id << "/" << value;
  return string.str();
}