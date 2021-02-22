//
// Created by andy on 30/1/21.
//

#ifndef TP_WOLFENSTEIN_IN_GAME_EVENT_GENERATOR_H
#define TP_WOLFENSTEIN_IN_GAME_EVENT_GENERATOR_H

#include <SDL_events.h>
#include <common/event.h>
#include <common/events.h>
#include <common/blocking_queue.h>
#include <common/shared_queue.h>
#include "client_player.h"
#include "in_game_event_handler.h"

class InGameEventGenerator {
 private:
  bool& game_running;
  bool& player_alive;
  bool& skip_stats;
  ClientPlayer& player;
  InGameEventHandler& event_handler;
  BlockingQueue<Event>& event_queue;
 public:
  InGameEventGenerator(ClientPlayer& _player,
                       InGameEventHandler& _event_handler,
                       BlockingQueue<Event>& _event_queue,
                       bool& _player_alive,
                       bool& _game_running,
                       bool& skip_stats);
  //Event parseEvent(SDL_Event event);
  void generateInGameEvent(SDL_Event sdl_event);
  void generateInGameEvents();

  bool playerQuitted();
};

#endif //TP_WOLFENSTEIN_IN_GAME_EVENT_GENERATOR_H
