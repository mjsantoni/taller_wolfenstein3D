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
#include <atomic>

#include "common/network_connection.h"
#include "server/game/client.h"

class GameHandler : public Thread {
private:
    //SharedQueue<Event> eventQueue;
    std::vector<Client*> clients;
    EventProcessor eventProcessor;
    std::atomic<bool> alive;

public:
    Game game;
    SharedQueue<Event> eventQueue;
    GameHandler(std::string map_path, std::string config_path);
    void run();

    void addNewPlayer(NetworkConnection fd);

    void stop();

    void notifyClients(std::vector<Change> &changes);
};


#endif //TP_WOLFENSTEIN_GAME_HANDLER_H
