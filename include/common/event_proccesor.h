#ifndef TP_WOLFENSTEIN_EVENT_PROCCESOR_H
#define TP_WOLFENSTEIN_EVENT_PROCCESOR_H

#include "event_queue.h"
#include "server/game/game.h"

class EventProccesor {
private:
    Game& game;
    EventQueue& eq;
public:
    EventProccesor(Game& _game, EventQueue& _eq);
    void process(Event& event);

};

#endif //TP_WOLFENSTEIN_EVENT_PROCCESOR_H
