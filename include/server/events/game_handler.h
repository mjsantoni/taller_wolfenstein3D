#ifndef TP_WOLFENSTEIN_GAME_HANDLER_H
#define TP_WOLFENSTEIN_GAME_HANDLER_H

#include <string>
#include <vector>
#include "common/event_factory.h"
#include "server/game/game.h"
#include "common/event_processor.h"
#include "common/shared_queue.h"
#include "common/blocking_queue.h"
#include "common/change.h"
#include "server/events/client_handler.h"
#include "server/events/client_updater.h"

#include "common/network_connection.h"

class GameHandler : public Thread {
private:
    //SharedQueue<Event> eventQueue;
    std::vector<ClientUpdater*> clients_updater;
    std::vector<ClientHandler*> clients_handler;
    std::vector<int> sockets;
    EventProcessor eventProcessor;
    bool alive = true;

public:
    Game game;
    SharedQueue<Event> eventQueue;
    GameHandler(std::string map_path, std::string config_path);
    void run();

    void addNewPlayer(int fd);

    void stop();
};


#endif //TP_WOLFENSTEIN_GAME_HANDLER_H
