#ifndef TP_WOLFENSTEIN_CLIENT_H
#define TP_WOLFENSTEIN_CLIENT_H

#include <vector>
#include <atomic>
#include <client/communication/server_updater.h>
#include "common/thread.h"
#include "client/communication/client_parser.h"
#include "map_mock.h"
#include "client_game.h"

class Client : public Thread {
private:


    int map_width;
    int map_height;
    ClientParser parser;
    std::atomic<bool> running;
    ServerUpdater updater;

public:
    Client(NetworkConnection &skt);
    void run() override;
    ~Client();
    void stop();
    bool isRunning();
};


#endif //TP_WOLFENSTEIN_CLIENT_H
