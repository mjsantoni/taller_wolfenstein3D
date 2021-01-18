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
#include "server/game/drop_handler.h"
#include "hit.h"

class Game {

private:
    std::atomic<bool> playing;
    std::vector<Player> players;
    MapParser mapParser;
    MapGenerator mapGenerator;
    Map map;
    ColissionHandler colHandler;
    PickUpHandler pickUpHandler;
    ConfigParser configParser;
    DropHandler dropHandler;
    int players_ids = 0;
    int players_alive = 0;

    //ShootHandler sh;

public:
    Game(std::string map_path, std::string config_path);
    std::pair<Coordinate, std::vector<Positionable>> movePlayer(int id);
    Hit shoot(int id);
    int connectPlayer();
    void rotate(int id, double angle);

    ~Game();

    void show();

    void changeGun(int id, int hotkey);

    bool isNotOver();

    void playerDies(Hit& hit);

    void addBulletsTo(int id, int bullets);

    void respawnPlayer(int &player);

    void killPlayerDefinitely(int &player);

    void dropPlayerItems(std::pair<std::pair<std::string, int>, int> drops, Coordinate coordinate);
};

#endif //TP_WOLFENSTEIN_GAME_H
