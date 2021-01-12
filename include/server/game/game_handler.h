#ifndef TP_WOLFENSTEIN_GAME_HANDLER_H
#define TP_WOLFENSTEIN_GAME_HANDLER_H

#include <string>
#include "common/event_queue.h"
#include "common/event_handler.h"
#include "game.h"
#include "common/event_proccesor.h"

class GameHandler {
private:
    Game game;
    EventQueue eq;
    EventHandler eh;
    EventProccesor ep;
public:
    GameHandler(std::string path);
    void run();

};


#endif //TP_WOLFENSTEIN_GAME_HANDLER_H
