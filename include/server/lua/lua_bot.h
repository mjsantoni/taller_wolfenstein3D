#ifndef TP_WOLFENSTEIN_LUA_BOT_H
#define TP_WOLFENSTEIN_LUA_BOT_H

#ifdef __cplusplus
// Este header es básicamente una inclusión de los 3 de abajo
// pero protegido con extern "C"
#include <lua5.3/lua.hpp>

#else
#include <lua5.3/lua.h>
  #include <lua5.3/lualib.h>
  #include <lua5.3/lauxlib.h>
#endif

#include "server/game/coordinate.h"
#include "server/lua/movement_calculator.h"
#include "common/shared_queue.h"
#include "common/event.h"
#include "server/game/player.h"
#include "common/thread.h"
#include <condition_variable>
#include <atomic>

class LuaBot : public Thread {
private:
    lua_State* L;
    Player& player;
    int id;
    SharedQueue<Event>& eventQueue;
    std::mutex m;
    std::condition_variable& cv;
    std::atomic<bool> alive;

    bool checkLua(lua_State* L, int r);

public:
    LuaBot(std::string lua_path, Player &_player, std::condition_variable &_cv, SharedQueue<Event>& sq);
    ~LuaBot();

    void popStack(int stack_elem_count);
    int getId();
    void setId(int id);

    void run() override;
    void stop();

    void addPositionable(Coordinate coord, std::string type);
    void addBlocking(Coordinate coord, std::string type);
    void addPlayer(Coordinate coord, int id);
    void printMap();

    void changeGun(int hotkey);
    void setGridSize(int size);
    void setAngleTurn(double angle_rotation);
    void setGunRange(int range);


    void updateAngle(double new_angle);
    void updatePosition(const Coordinate& coord);
    void cleanMap();


    void closestTarget();
    void proccessEvents();
    static int isInSight(lua_State* L);
    static int move(lua_State* L);

    static bool isABlockingItemAt(lua_State *L, const Coordinate &coord, int stack_pos);

    std::vector<int> getEvents();

    void pushEvents(std::vector<int> events);

    void sendLives(int i);
};


#endif //TP_WOLFENSTEIN_LUA_BOT_H
