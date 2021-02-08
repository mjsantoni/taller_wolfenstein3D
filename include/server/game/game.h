#ifndef TP_WOLFENSTEIN_SERVER_GAME_H
#define TP_WOLFENSTEIN_SERVER_GAME_H

#include <atomic>
#include <string>
#include <chrono>
#include <ctime>

#include <condition_variable>
#include <atomic>

#include "colission_handler.h"
#include "common/config_parser.h"
#include "hit.h"
#include "player.h"
#include "pickup_handler.h"
#include "common/thread.h"
#include "common/change.h"
#include "server/game/blocking_item_handler.h"
#include "server/game/drop_handler.h"
#include "server/game/map_generator.h"
#include "common/map_parser.h"
#include "server/game/shoot_handler.h"
#include "server/events/hit_handler.h"
#include "server/lua/lua_bot.h"
#include "server/lua/bots_manager.h"
#include "server/game/score_handler.h"

class Game {
private:
    std::vector<Player> players;
    MapParser mapParser;
    MapGenerator mapGenerator;
    Map map;
    ConfigParser configParser;
    ScoreHandler scoreHandler;
    ColissionHandler colHandler;
    BlockingItemHandler blockingItemHandler;
    ShootHandler shootHandler;
    PickUpHandler pickUpHandler;
    DropHandler dropHandler;
    HitHandler hitHandler;
    std::map<Coordinate,int> doors_to_close;
    std::chrono::time_point<std::chrono::system_clock> time_start;


    std::set<int> players_ready;
    int players_ids = 0;
    int players_alive = 0;

    /* Bot stuff */
    BotsManager& botsManager;
    std::mutex m;
    std::condition_variable cv;

    /* Functions */
    static double getAngleToMove(int direction);

public:
    Game(std::string map_path, std::string config_path, BotsManager& bm);
    ~Game();

    /* RECEIVED EVENTS */
    std::pair<int,std::map<Coordinate, Positionable>> connectPlayer();
    std::pair<Coordinate, std::vector<Positionable>> movePlayer(int id, int move_direction);
    std::pair<Hit, std::vector<Change>> shoot(int id);
    std::pair<bool, int> openDoor(int id);
    int pushWall(int id);
    void rotate(int id, int rotation);
    void changeGun(int id, int hotkey);
    void playerIsReady(int i);

    /* GAME CHECK */
    bool isNotOver();
    int getPlayersAlive();
    bool isReady();

    /* GAME CHANGERS */
    void playerDies(Hit& hit);
    void addDropsToHitEvent(const std::pair<std::string, bool> &drops,
                            Hit &hit, const Coordinate& pos);
    void closeDoors(std::vector<Change>& vector);
    std::vector<Change> passTime();

    /* GAME PRINT */
    void show();

    void addBot();
    void releaseBots();

    int getPlayersConnected() const;
    std::vector<std::pair<int, int>> getTop(std::string type, int n);
};

#endif //TP_WOLFENSTEIN_SERVER_GAME_H
