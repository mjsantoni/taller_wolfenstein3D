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

    int players_n;
    int bots_n;
    int game_id;

public:
    GameHandler(const std::string &map_path, const std::string &config_path, int _players_n, int _bots_n,
                int _game_id);
    void run() override;

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
