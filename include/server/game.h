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
    std::vector<Player> players;
    //ShootHandler sh;

public:
    Game(std::string path);
    void movePlayer(int id, double angle);
    void shoot(int id, double angle);
    ~Game();

    void show();
};

#endif //TP_WOLFENSTEIN_GAME_H
