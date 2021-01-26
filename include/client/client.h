#ifndef TP_WOLFENSTEIN_CLIENT_H
#define TP_WOLFENSTEIN_CLIENT_H

#include <vector>
#include <atomic>
#include "common/thread.h"
#include "client_parser.h"
#include "map_mock.h"
#include "client_game.h"

class Client : public Thread {
private:
    int map_width;
    int map_height;
    ClientParser parser;
    std::atomic<bool> running;

public:
    Client();
    void run() override;
    ~Client();
    void stop();
    bool isRunning();
};


#endif //TP_WOLFENSTEIN_CLIENT_H
