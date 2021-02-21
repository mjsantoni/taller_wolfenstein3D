//
// Created by andy on 11/2/21.
//

#ifndef TP_WOLFENSTEIN_OFF_GAME_EVENT_GENERATOR_H
#define TP_WOLFENSTEIN_OFF_GAME_EVENT_GENERATOR_H


#include <common/event.h>
#include <common/blocking_queue.h>
#include "client_player.h"

class OffGameEventGenerator {
private:
    BlockingQueue<Event>& event_queue;
    ClientPlayer& player;
    bool ready_event_already_sent = false;
public:
    OffGameEventGenerator(BlockingQueue<Event>& _event_queue,
                          ClientPlayer& _player);
    void generateReadyEventIfNecessary();
};


#endif //TP_WOLFENSTEIN_OFF_GAME_EVENT_GENERATOR_H
