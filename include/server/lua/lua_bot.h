#ifndef TP_WOLFENSTEIN_LUA_BOT_H
#define TP_WOLFENSTEIN_LUA_BOT_H

#include <atomic>
#include <condition_variable>
#include "server/lua/lua_engine.h"
#include "common/shared_queue.h"
#include "common/event.h"
#include "server/game/player.h"
#include "common/thread.h"

class LuaBot : public Thread {
private:
    LuaEngine luaEngine;
    Player& player;
    int id;
    SharedQueue<Event>& eventQueue;
    std::mutex m;
    std::condition_variable& cv;
    std::atomic<bool> alive;


public:
    LuaBot(std::string lua_path, Player &_player, std::condition_variable &_cv, SharedQueue<Event>& sq);

    ~LuaBot();
    int getId();

    void setId(int id);
    void run() override;

    void stop();
    void addPositionable(Coordinate coord, std::string type);
    void addBlocking(Coordinate coord, std::string type);

    void addPlayer(Coordinate coord, int id);
    void setGridSize(int size);
    void setAngleTurn(double angle_rotation);

    void setGunRange(int range);
    void updatePosition(const Coordinate& coord);

    void cleanMap();
    void closestTarget();

    void proccessEvents();

    void pushEvents(std::vector<int> events);
    std::vector<int> getEvents();
    void sendLives(int i);
};


#endif //TP_WOLFENSTEIN_LUA_BOT_H
