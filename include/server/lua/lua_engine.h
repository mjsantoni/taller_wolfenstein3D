#ifndef TP_WOLFENSTEIN_LUA_ENGINE_H
#define TP_WOLFENSTEIN_LUA_ENGINE_H

#ifdef __cplusplus
#include <lua5.3/lua.hpp>
#else
#include <lua5.3/lua.h>
  #include <lua5.3/lualib.h>
  #include <lua5.3/lauxlib.h>
#endif

#include <vector>
#include "common/coordinate.h"
#include "server/lua/movement_calculator.h"

class LuaEngine {
private:
    lua_State* L;
public:
    LuaEngine(std::string& path);

    void pushFunction(std::string func);
    void push(std::string& value);
    void push(int value);
    void pushTable(int value);
    void pushNill();
    void callFunction(int recv, int back);
    void getEvents(std::vector<int>& events);

    static int isInSight(lua_State* L);
    static int move(lua_State* L);
    static bool isABlockingItemAt(lua_State *L, const Coordinate &coord, int stack_pos);

    ~LuaEngine();

};


#endif //TP_WOLFENSTEIN_LUA_ENGINE_H
