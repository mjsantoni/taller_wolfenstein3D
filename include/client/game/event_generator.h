//
// Created by andy on 30/1/21.
//

#ifndef TP_WOLFENSTEIN_EVENT_GENERATOR_H
#define TP_WOLFENSTEIN_EVENT_GENERATOR_H

#include <SDL_events.h>
#include <common/event.h>
#include <common/events.h>
#include <common/blocking_queue.h>
#include "client_player.h"
#include "client_event_handler.h"
#include "client/communication/server_updater.h"

class EventGenerator {
private:
    bool is_running = true;
    ClientPlayer& player;
    ClientEventHandler& event_handler;
    ServerUpdater& server_updater;
public:
    EventGenerator(ClientPlayer& _player, ClientEventHandler& _event_handler,
                   ServerUpdater& _server_updater);
    void stop();
    //Event parseEvent(SDL_Event event);
    void generateInGameEvent(SDL_Event sdl_event);
    void generateConnectedPlayerEvent(SDL_Event sdl_event);
};


#endif //TP_WOLFENSTEIN_EVENT_GENERATOR_H
