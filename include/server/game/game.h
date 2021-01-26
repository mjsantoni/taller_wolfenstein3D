#ifndef TP_WOLFENSTEIN_SERVER_GAME_H
#define TP_WOLFENSTEIN_SERVER_GAME_H

#include <atomic>
#include <string>
#include "colission_handler.h"
#include "config_parser.h"
#include "hit.h"
#include "player.h"
#include "pickup_handler.h"
#include "common/thread.h"
#include "common/change.h"
#include "server/game/blocking_item_handler.h"
#include "server/game/drop_handler.h"
#include "server/game/map_generator.h"
#include "server/game/map_parser.h"

class Game {
private:
    std::vector<Player> players;
    MapParser mapParser;
    MapGenerator mapGenerator;
    Map map;
    ColissionHandler colHandler;
    PickUpHandler pickUpHandler;
    ConfigParser configParser;
    DropHandler dropHandler;
    BlockingItemHandler blockingItemHandler;
    std::map<Coordinate,int> rpgs;
    std::map<Coordinate,int> doors_to_close;

    int players_ids = 0;
    int players_alive = 0;

public:
    Game(std::string map_path, std::string config_path);
    ~Game();

    /* RECEIVED EVENTS */
    int connectPlayer();
    std::pair<Coordinate, std::vector<Positionable>> movePlayer(int id);
    Hit shoot(int id);
    std::pair<bool, int> openDoor(int id);
    int pushWall(int id);
    void rotate(int id, double angle);
    void changeGun(int id, int hotkey);

    /* GAME CHECK */
    bool isNotOver();
    int getPlayersAlive();

    /* GAME CHANGERS */
    void playerDies(Hit& hit);
    void addDropsToHitEvent(const std::pair<std::string, bool> &drops,
                            Hit &hit, const Coordinate& pos);
    void closeDoors(std::vector<Change>& vector);
    std::vector<Change> passTime();

    /* GAME PRINT */
    void show();
};

#endif //TP_WOLFENSTEIN_SERVER_GAME_H
