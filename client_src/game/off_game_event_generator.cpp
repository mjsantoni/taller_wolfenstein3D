//
// Created by andy on 11/2/21.
//

#include "client/game/off_game_event_generator.h"

OffGameEventGenerator::OffGameEventGenerator(BlockingQueue<Event> &_event_queue,
                                             ClientPlayer &_player) :
                                             event_queue(_event_queue),
                                             player(_player) {

}

void OffGameEventGenerator::generateReadyEventIfNecessary() {
    if (ready_event_already_sent)
        return;
    Event event = Event(PLAYER_READY, player.getId(), 0);
    event_queue.push(event);
    ready_event_already_sent = true;
}
