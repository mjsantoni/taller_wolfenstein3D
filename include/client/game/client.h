#ifndef TP_WOLFENSTEIN_CLIENT_H
#define TP_WOLFENSTEIN_CLIENT_H

#include <vector>
#include <atomic>
#include <client/communication/server_updater.h>
#include <client/communication/server_listener.h>
#include "common/thread.h"
#include "client/communication/client_parser.h"
#include "map_mock.h"
#include "client_game_handler.h"

class Client {
private:
    ClientParser parser;
    std::atomic<bool> running;
    ServerUpdater server_updater;
    ServerListener server_listener;
    SharedQueue<Change> change_queue;

public:
    explicit Client(NetworkConnection &skt);
    void start();
    void stop();
    bool isRunning();
};


#endif //TP_WOLFENSTEIN_CLIENT_H
