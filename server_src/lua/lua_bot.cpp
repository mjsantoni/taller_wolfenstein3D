#include <string>
#include <iostream>
#include <cmath>
#include "server/lua/lua_bot.h"

LuaBot::LuaBot(std::string _name, std::string lua_path, int _id) :
                L(luaL_newstate()), name(_name), id(_id) {
    luaL_openlibs(L);
    if(!checkLua(L, luaL_dofile(L, lua_path.c_str()))) return; // carga el script
    // deberia levantar una excepcion
    setId(_id);

    // Register our C++ Function in the global Lua space
    lua_register(L, "isInSight", isInSight);
    lua_register(L, "move", move);
    lua_register(L, "createMoveEvent", createMoveEvent);
    lua_register(L, "createRotateCameraEvent", createRotateCameraEvent);
    lua_register(L, "createPicanazoEvent", createPicanazoEvent);
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

void LuaBot::updateAngle(double new_angle) {
    lua_getglobal(L, "updateAngle");
    lua_pushnumber(L, new_angle);
    lua_pcall(L, 1, 0, 0);
}

void LuaBot::cleanMap() {
    lua_getglobal(L, "cleanMap");
    lua_pcall(L, 0, 0, 0);
}

void LuaBot::updatePosition(const Coordinate& coord) {
    lua_getglobal(L, "updatePosition");
    lua_pushnumber(L, coord.x);
    lua_pushnumber(L, coord.y);
    lua_pcall(L, 2, 0, 0);
}

bool LuaBot::isABlockingItemAt(lua_State *L, const Coordinate &coord, int stack_pos) {
    lua_getglobal(L, "isABlockingItemAt");
    lua_pushnumber(L, coord.x);
    lua_pushnumber(L, coord.y);
    lua_pcall(L,2,1,0);
    bool is_blocking = lua_toboolean(L, stack_pos);
    lua_pop(L, 1);
    return is_blocking;
}

int LuaBot::isInSight(lua_State *L) {
    /* Necesito sacar los 4 elementos del stack */
    int x_old = lua_tonumber(L, 1);
    int y_old = lua_tonumber(L, 2);
    int x_new = lua_tonumber(L, 3);
    int y_new = lua_tonumber(L, 4);

    Coordinate actual(x_old,y_old);
    Coordinate future(x_new,y_new);
    MovementCalculator mc;
    std::vector<Coordinate> path = mc.straightLine(actual,future);
    for (auto& coord : path) {
        bool is_blocking = isABlockingItemAt(L, coord, 5);
        if (is_blocking) {
            lua_pushnumber(L, 0); // cargo un 0 para indicar q encontre un blocking
            return 1;
        }
    }
    lua_pushnumber(L, 1); // no hay paredes en el medio
    return 1;
}

void LuaBot::closestTarget() {
    lua_getglobal(L, "closestTarget"); // Get function to stack
    lua_pcall(L, 0, 0, 0);
}

int LuaBot::move(lua_State *L) {
    /* Necesito sacar los 3 elementos del stack */
    int current_x = lua_tonumber(L, 1);
    int current_y = lua_tonumber(L, 2);
    double current_angle = lua_tonumber(L, 3);
    Coordinate current(current_x, current_y);
    std::cout << "[CPP] Angle: " << current_angle << " - "; current.show();

    MovementCalculator mc;
    Coordinate new_pos = mc.moveToPosition(current, current_angle, L, 4);
    lua_pushnumber(L, new_pos.x);
    lua_pushnumber(L, new_pos.y);
    return 2;
}

int LuaBot::createMoveEvent(lua_State* L) {
    std::cout << "[CPP] Se crea un moveEvent\n";
    //eventQueue.push(Event(MOVE_PLAYER, id, INVALID));
    return 0;
}

int LuaBot::createRotateCameraEvent(lua_State* L) {
    int amount = lua_tonumber(L, 1);
    int turn_direction = lua_tonumber(L, 2);
    std::cout << "[CPP] Se crea un rotateCameraEvent ";
    std::cout << "cuyo amount es: " << amount << " - turn_dir: " << turn_direction << "\n";
    for (int i = 0; i < amount; i++) {
        //eventQueue.push(Event(TURN_CAMERA, turn_direction, 0));
    }
    return 0;
}

int LuaBot::createPicanazoEvent(lua_State *L) {
    std::cout << "[CPP] Se crea un picanazo event\n";
    //eventQueue.push(Event(SHOOT, id, INVALID));
    return 0;
}
