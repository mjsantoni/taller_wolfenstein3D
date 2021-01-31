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

class LuaBot {
public:
    lua_State* L;
    std::string name;
    LuaBot(std::string _name) : L(luaL_newstate()), name(_name) {

        luaL_openlibs(L);
        if(!CheckLua(L, luaL_dofile(L, "../server_src/lua/bot.lua"))) return; // carga el script
    }

    bool CheckLua(lua_State *L, int r) {
        if (r == LUA_OK) return true;
        std::string errormsg = lua_tostring(L, -1);
        std::cout << errormsg << std::endl;
        return false;
    }
};


#endif //TP_WOLFENSTEIN_LUA_BOT_H
