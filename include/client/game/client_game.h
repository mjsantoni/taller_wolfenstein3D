//
// Created by andy on 5/2/21.
//

#ifndef TP_WOLFENSTEIN_CLIENT_GAME_H
#define TP_WOLFENSTEIN_CLIENT_GAME_H

#include <common/thread.h>
#include <client/communication/server_updater.h>
#include <client/communication/server_listener.h>
#include "client_map.h"
#include "client_game_handler.h"

class ClientGame : public Thread {
public:
    ClientGame(ServerUpdater& _server_updater, ServerListener& _server_handler,
               ClientMap& _map, SharedQueue<Change>& change_queue,
               BlockingQueue<Event>& event_queue);
    bool isRunning();
    ~ClientGame();
    void run() override;
    void stop();
private:
    ServerUpdater& server_updater;
    ServerListener& server_handler;
    ClientGameHandler game_handler;
    std::atomic<bool> alive;
};


#endif //TP_WOLFENSTEIN_CLIENT_GAME_H
