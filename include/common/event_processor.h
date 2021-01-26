#ifndef TP_WOLFENSTEIN_EVENT_PROCESSOR_H
#define TP_WOLFENSTEIN_EVENT_PROCESSOR_H

#include "server/game/game.h"
#include "common/change.h"
#include "common/event.h"
#include "server/game/config_parser.h"

class EventProcessor {
private:
    Game& game;
    ConfigParser configParser;

public:
    EventProcessor(Game &_game, std::string config_path);
    std::vector<Change> process(Event& event);

};

#endif //TP_WOLFENSTEIN_EVENT_PROCESSOR_H
