#include <string>
#include <iostream>
#include "server/entities/lua_bot.h"

LuaBot::LuaBot(std::string _name, std::string lua_path) : L(luaL_newstate()), name(_name) {
    luaL_openlibs(L);
    if(!checkLua(L, luaL_dofile(L, lua_path.c_str()))) return; // carga el script
    // deberia levantar una excepcion
}

bool LuaBot::checkLua(lua_State *L, int r) {
    if (r == LUA_OK) return true;
    std::string errormsg = lua_tostring(L, -1);
    std::cout << errormsg << std::endl;
    return false;
}

const std::string& LuaBot::getName() const { return name; }

void LuaBot::addToMap(int id, Coordinate coord, std::string type) {
    lua_getglobal(L, "addToMap"); // Get function to stack
    lua_pushnumber(L, id);
    lua_pushstring(L, type.c_str()); //podria ser mas generico (getCategory)
    lua_pushnumber(L, coord.x);
    lua_pushnumber(L, coord.y);
    // std::cout << "[CPP] Calling 'addToMap'\n";
    // Lua pcall recibe: L, cant argumentos de la funcion, cant cosas que devuelve, how to handle error
    lua_pcall(L, 4, 0, 0); // Al ejecutar la funcion se popea todo del stack (si no devuelve nada)
}

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
