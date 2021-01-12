#ifndef TP_WOLFENSTEIN_GAME_H
#define TP_WOLFENSTEIN_GAME_H

#include <string>
#include "common/thread.h"
#include <atomic>
#include "colission_handler.h"
#include "pickup_handler.h"
#include "player.h"
#include "config_parser.h"
#include "server/game/map_generator.h"
#include "server/game/map_parser.h"

class Game {

private:
    std::atomic<bool> playing;
    std::vector<Player> players;
    MapParser mapParser;
    MapGenerator mapGenerator;
    Map map;
    PickUpHandler ph;
    ColissionHandler colHandler;

    //ShootHandler sh;

public:
    Game(std::string map_path, std::string config_path);
    void movePlayer(int id, double angle);
    void shoot(int id, double angle);
    ~Game();

    void show();
};

#endif //TP_WOLFENSTEIN_GAME_H
