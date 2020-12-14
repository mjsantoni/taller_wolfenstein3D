#ifndef TP_WOLFENSTEIN_GAME_HANDLER_H
#define TP_WOLFENSTEIN_GAME_HANDLER_H

#include <string>
#include "event_queue.h"
#include "event_handler.h"
#include "server/game.h"
#include "event_proccesor.h"

class GameHandler {
private:
    Game game;
    EventQueue eq;
    EventHandler eh;
    EventProcessor ep;
    std::vector<ClientHandler*> clients;
public:
    GameHandler(std::string path);
    void run();

};


#endif //TP_WOLFENSTEIN_GAME_HANDLER_H
