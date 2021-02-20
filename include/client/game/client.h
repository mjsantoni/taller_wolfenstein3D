#ifndef TP_WOLFENSTEIN_CLIENT_H
#define TP_WOLFENSTEIN_CLIENT_H

#include <vector>
#include <atomic>
#include <client/communication/server_updater.h>
#include <client/communication/server_listener.h>
#include "common/thread.h"
#include "client_game.h"
#include <common/network_connection.h>
#include <client/communication/server_updater.h>
#include <client/game/client_game.h>
#include <common/connection_exception.h>


class Client {
private:
    std::atomic<bool> running;
    ServerUpdater server_updater;
    ServerListener server_listener;
    SharedQueue<Change> change_queue;
    BlockingQueue<Event> event_queue;

public:
    explicit Client(NetworkConnection &skt);
    void startGame(const std::string& map_name);
    void stop();
    bool isRunning();
};


#endif //TP_WOLFENSTEIN_CLIENT_H
