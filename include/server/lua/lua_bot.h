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

class LuaBot {
private:
    std::string name;
    lua_State* L;
    int id;
    //SharedQueue<Event>& eventQueue;

    bool checkLua(lua_State* L, int r);

public:
    LuaBot(std::string _name, std::string lua_path, int _id);
    const std::string &getName() const;
    void popStack(int stack_elem_count);

    void addPositionable(Coordinate coord, std::string type);
    void addBlocking(Coordinate coord, std::string type);
    void addPlayer(Coordinate coord, int id);
    void setId(int id);
    void printMap();
    void updateAngle(double new_angle);
    void updatePosition(const Coordinate& coord);
    void cleanMap();


    void closestTarget();
    static int isInSight(lua_State* L);
    static int move(lua_State* L);
    static int createMoveEvent(lua_State *L);
    static int createRotateCameraEvent(lua_State *L);

    static bool isABlockingItemAt(lua_State *L, const Coordinate &coord, int stack_pos);

};


#endif //TP_WOLFENSTEIN_LUA_BOT_H
