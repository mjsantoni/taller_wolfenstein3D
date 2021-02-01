#include <string>
#include <iostream>
#include <cmath>
#include "server/entities/lua_bot.h"

LuaBot::LuaBot(std::string _name, std::string lua_path, int _id) :
                L(luaL_newstate()), name(_name), id(_id) {
    luaL_openlibs(L);
    if(!checkLua(L, luaL_dofile(L, lua_path.c_str()))) return; // carga el script
    // deberia levantar una excepcion
    setId(_id);

    // Register our C++ Function in the global Lua space
    lua_register(L, "isInSight", isInSight);
}

bool LuaBot::checkLua(lua_State *L, int r) {
    if (r == LUA_OK) return true;
    std::string errormsg = lua_tostring(L, -1);
    std::cout << errormsg << std::endl;
    return false;
}

const std::string& LuaBot::getName() const { return name; }

void LuaBot::printMap() {
    //std::cout << "[CPP] Get printMap\n";
    lua_getglobal(L, "printMap");
    //std::cout << "[CPP] Calling 'printMap'\n";
    lua_pcall(L, 0, 0, 0);
}

void LuaBot::popStack(int stack_elem_count) {
    for (int i = 0; i < stack_elem_count; i++) {
        lua_pop(L, 1);
    }
}

void LuaBot::addPositionable(Coordinate coord, std::string type) {
    lua_getglobal(L, "addPositionable"); // Get function to stack
    lua_pushnumber(L, coord.x);
    lua_pushnumber(L, coord.y);
    lua_pushstring(L, type.c_str());
    lua_pcall(L, 3, 0, 0);
}

void LuaBot::addBlocking(Coordinate coord, std::string type) {
    lua_getglobal(L, "addBlocking"); // Get function to stack
    lua_pushnumber(L, coord.x);
    lua_pushnumber(L, coord.y);
    lua_pushstring(L, type.c_str());
    lua_pcall(L, 3, 0, 0);
}

void LuaBot::addPlayer(Coordinate coord, int id) {
    lua_getglobal(L, "addPlayer"); // Get function to stack
    lua_pushnumber(L, coord.x);
    lua_pushnumber(L, coord.y);
    lua_pushnumber(L, id);
    lua_pcall(L, 3, 0, 0);
}

void LuaBot::setId(int id) {
    lua_getglobal(L, "setId"); // Get function to stack
    lua_pushnumber(L, id);
    lua_pcall(L, 1, 0, 0);
}

int LuaBot::isInSight(lua_State *L) {
    /* Necesito sacar los 4 elementos del stack */
    int x_old = lua_tonumber(L, 1);
    int y_old = lua_tonumber(L, 2);
    int x_new = lua_tonumber(L, 3);
    int y_new = lua_tonumber(L, 4);

    Coordinate actual(x_old,y_old);
    Coordinate future(x_new,y_new);
    PositionsCalculator pc;
    std::vector<Coordinate> path = pc.straightLine(actual,future);
    for (auto& coord : path) {
        lua_getglobal(L, "isABlockingItemAt");
        lua_pushnumber(L, coord.x);
        lua_pushnumber(L, coord.y);
        lua_pcall(L,2,1,0);
        bool is_blocking = lua_toboolean(L, 5);
        lua_pop(L, 1);
        if (is_blocking) {
            lua_pushnumber(L, 0); // cargo un 0 para indicar q encontre un blocking
            return 1;
        }
    }
    lua_pushnumber(L, 1); // no hay paredes en el medio
    return 1;
}

void LuaBot::closestTarget(int x1, int x2, int x3, int x4) {
    lua_getglobal(L, "closestTarget"); // Get function to stack
    lua_pcall(L, 0, 0, 0);
}
