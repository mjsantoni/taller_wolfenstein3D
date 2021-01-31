#include <string>
#include <iostream>
#include "server/entities/lua_bot.h"

LuaBot::LuaBot(std::string _name, std::string lua_path, int _id) :
                L(luaL_newstate()), name(_name), id(_id) {
    luaL_openlibs(L);
    if(!checkLua(L, luaL_dofile(L, lua_path.c_str()))) return; // carga el script
    // deberia levantar una excepcion
    setId(_id);
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
