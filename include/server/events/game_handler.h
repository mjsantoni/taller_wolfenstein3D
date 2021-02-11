#ifndef TP_WOLFENSTEIN_GAME_HANDLER_H
#define TP_WOLFENSTEIN_GAME_HANDLER_H

#include <string>
#include <vector>
#include "common/event_factory.h"
#include "server/game/game.h"
#include "event_processor.h"
#include "common/shared_queue.h"
#include "common/blocking_queue.h"
#include "common/change.h"
#include "server/events/client_handler.h"
#include "server/events/client_updater.h"
#include <atomic>

#include "common/network_connection.h"
#include "server/game/client.h"
#include "../server_src/clients_manager.h"

class GameHandler : public Thread {
private:
    SharedQueue<Event> eventQueue;
    BotsManager botsManager;
    Game game;
    ClientsManager clientsManager;
    EventProcessor eventProcessor;
    std::atomic<bool> alive;
    std::atomic<bool> can_join_player;
    std::mutex m;
    std::condition_variable cv;

    int players_n;
    int bots_n;

public:
    GameHandler(std::string map_path, std::string config_path, int _players_n, int _bots_n);
    void run();

    void addNewPlayer(NetworkConnection fd);

    void stop();

    void notifyClients(std::vector<Change> &changes);

    void waitInLobby();

    void sendTops();

    void notifyTop(std::vector<std::pair<int, int>> top, int change_id);

    void addBots();

    bool canJoinPlayer();

    bool ended();

    void endGame();
};


#endif //TP_WOLFENSTEIN_GAME_HANDLER_H
