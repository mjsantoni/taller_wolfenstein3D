#ifndef TP_WOLFENSTEIN_SERVER_H
#define TP_WOLFENSTEIN_SERVER_H

#include <string>
#include "common/thread.h"
#include <atomic>
#include "server/colission_handler.h"
#include "server/pickup_handler.h"
#include "server/player.h"

class Server {
private:
    std::string path;
    std::atomic<bool> playing;
    Map map;
    PickUpHandler ph;
    ColissionHandler ch;
public:
    Server(std::string path);
    void movePlayer(Player& player, double angle);
    ~Server();

};

#endif //TP_WOLFENSTEIN_SERVER_H
