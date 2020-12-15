#ifndef TP_WOLFENSTEIN_GAME_H
#define TP_WOLFENSTEIN_GAME_H

#include <string>
#include "common/thread.h"
#include <atomic>
#include "server/colission_handler.h"
#include "server/pickup_handler.h"
#include "server/player.h"

class Game {

private:
    std::string path;
    std::atomic<bool> playing;
    Map map;
    PickUpHandler ph;
    ColissionHandler ch;
    //ShootHandler sh;

public:
    Game(std::string path);
    void movePlayer(Player& player, double angle);
    ~Game();

};

#endif //TP_WOLFENSTEIN_GAME_H
