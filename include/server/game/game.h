#ifndef TP_WOLFENSTEIN_SERVER_GAME_H
#define TP_WOLFENSTEIN_SERVER_GAME_H

#include <atomic>
#include <chrono>
#include <ctime>
#include <string>

#include "colission_handler.h"
#include "common/change.h"
#include "common/config_parser.h"
#include "common/map_parser.h"
#include "common/thread.h"
#include "hit.h"
#include "player.h"
#include "pickup_handler.h"
#include "server/events/hit_handler.h"
#include "server/game/blocking_item_handler.h"
#include "server/game/drop_handler.h"
#include "server/game/map_generator.h"
#include "server/game/score_handler.h"
#include "server/game/shoot_handler.h"
#include "server/lua/bots_manager.h"
#include "server/lua/lua_bot.h"

class Game {
private:
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
    std::vector<Player> players;

    std::map<Coordinate,int> doors_to_close;
    std::chrono::time_point<std::chrono::system_clock> time_start;

    std::set<int> players_ready;
    int players_ids = 0;
    int players_alive = 0;
    int players_requested;

    /* Bot stuff */
    BotsManager& botsManager;
    std::mutex m;

    /* Functions */
    static double getAngleToMove(int direction);

public:
    Game(std::string map_path, std::string config_path, BotsManager& bm, int _player_requested);
    ~Game();

    /* RECEIVED EVENTS */
    std::pair<int,std::unordered_map<Coordinate, Positionable, Coordinate::HashFunction>> connectPlayer();
    std::pair<Coordinate, std::vector<Positionable>> movePlayer(int id, int move_direction);
    std::pair<Hit, std::vector<Change>> shoot(int id);
    std::pair<bool, int> openDoor(int id);
    int pushWall(int id);
    void rotate(int id, int rotation);
    int changeGun(int id, int hotkey);
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
    std::vector<std::pair<int, int>> getTop(std::string type, int n);

    /* LUA SCRIPT */
    void addBot();
    void releaseBots();
};

#endif //TP_WOLFENSTEIN_SERVER_GAME_H
