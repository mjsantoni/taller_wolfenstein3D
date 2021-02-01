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
#include "server/game/positions_calculator.h"

class LuaBot {
private:
    bool checkLua(lua_State* L, int r);
    std::string name;
    lua_State* L;
    int id;


public:
    LuaBot(std::string _name, std::string lua_path, int _id);
    const std::string &getName() const;
    void popStack(int stack_elem_count);

    void addPositionable(Coordinate coord, std::string type);
    void addBlocking(Coordinate coord, std::string type);
    void addPlayer(Coordinate coord, int id);
    void setId(int id);

    static int isInSight(lua_State* L);
    void closestTarget(int x1, int x2, int x3, int x4);

    void printMap();

};


#endif //TP_WOLFENSTEIN_LUA_BOT_H
