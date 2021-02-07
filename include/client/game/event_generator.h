//
// Created by andy on 30/1/21.
//

#ifndef TP_WOLFENSTEIN_EVENT_GENERATOR_H
#define TP_WOLFENSTEIN_EVENT_GENERATOR_H

#include <SDL_events.h>
#include <common/event.h>
#include <common/events.h>
#include <common/blocking_queue.h>
#include <common/shared_queue.h>
#include "client_player.h"
#include "client_event_handler.h"

class EventGenerator {
private:
    bool is_running = true;
    ClientPlayer& player;
    ClientEventHandler& event_handler;
    BlockingQueue<Event>& event_queue;
public:
    EventGenerator(ClientPlayer& _player, ClientEventHandler& _event_handler,
                   BlockingQueue<Event>& _event_queue);
    void stop();
    //Event parseEvent(SDL_Event event);
    void generateInGameEvent(SDL_Event sdl_event);
    void generateConnectedPlayerEvent(SDL_Event sdl_event);
};


#endif //TP_WOLFENSTEIN_EVENT_GENERATOR_H
