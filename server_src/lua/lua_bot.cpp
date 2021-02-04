#include <string>
#include <iostream>
#include <cmath>
#include "server/lua/lua_bot.h"

LuaBot::LuaBot(std::string lua_path, Player &_player, std::condition_variable &_cv, SharedQueue<Event>& eq) :
        L(luaL_newstate()), player(_player),
        id(player.getID()), cv(_cv), alive(true),
        eventQueue(eq) {
    luaL_openlibs(L);
    if(!checkLua(L, luaL_dofile(L, lua_path.c_str()))) return; // carga el script
    // deberia levantar una excepcion
    setId(id);

    // Register our C++ Function in the global Lua space
    lua_register(L, "isInSight", isInSight);
    lua_register(L, "move", move);
    changeGun(1); // Esto lo tiene que hacer el script del bot.
}

LuaBot::~LuaBot() { lua_close(L); }

bool LuaBot::checkLua(lua_State *L, int r) {
    if (r == LUA_OK) return true;
    std::string errormsg = lua_tostring(L, -1);
    //std::cout << errormsg << std::endl;
    return false;
}

int LuaBot::getId() { return id; }

/* EJECUCION */

void LuaBot::run() {
    while (alive) {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock);
        if (!alive) break;
        closestTarget();
        proccessEvents();
    }
}

void LuaBot::closestTarget() {
    //std::unique_lock<std::mutex> lock(m); // Por ahora no genera RC
    lua_getglobal(L, "closestTarget"); // Get function to stack
    lua_pcall(L, 0, 0, 0);
}

void LuaBot::proccessEvents() {
    std::vector<int> events = getEvents();
    std::cout << "Vector de eventos de Lua\n";
    for (int i : events) {
        std::cout << i << "\n";
    }
    pushEvents(events);
}

std::vector<int> LuaBot::getEvents() {
    std::vector<int> events;
    lua_getglobal(L, "getEvents");
    lua_pcall(L, 0, 1, 0);
    lua_pushvalue(L, -1);
    lua_pushnil(L);
    while (lua_next(L, -2)) {
        events.push_back(lua_tonumber(L, -1));
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
    return events;
}

void LuaBot::pushEvents(std::vector<int> events) {

    std::cout << "Tamaño del vector: " << events.size() << "\n";
    for(int i = 0; i < (int) events.size(); i += 3) {
        eventQueue.push(Event(events[i],events[i+1],events[i+2]));
    }

}

void LuaBot::stop() {
    alive = false;
}


/* ADDERS API */

void LuaBot::addPositionable(Coordinate coord, std::string type) {
    std::unique_lock<std::mutex> lock(m);
    lua_getglobal(L, "addPositionable"); // Get function to stack
    lua_pushnumber(L, coord.x);
    lua_pushnumber(L, coord.y);
    lua_pushstring(L, type.c_str());
    lua_pcall(L, 3, 0, 0);
}

void LuaBot::addBlocking(Coordinate coord, std::string type) {
    std::unique_lock<std::mutex> lock(m);
    lua_getglobal(L, "addBlocking"); // Get function to stack
    lua_pushnumber(L, coord.x);
    lua_pushnumber(L, coord.y);
    lua_pushstring(L, type.c_str());
    lua_pcall(L, 3, 0, 0);
}

void LuaBot::addPlayer(Coordinate coord, int id) {
    std::unique_lock<std::mutex> lock(m);
    lua_getglobal(L, "addPlayer"); // Get function to stack
    lua_pushnumber(L, coord.x);
    lua_pushnumber(L, coord.y);
    lua_pushnumber(L, id);
    lua_pcall(L, 3, 0, 0);
}

/* SETTERS */

void LuaBot::setId(int id) {
    lua_getglobal(L, "setId"); // Get function to stack
    lua_pushnumber(L, id);
    lua_pcall(L, 1, 0, 0);
}

void LuaBot::setGridSize(int size) {
    lua_getglobal(L, "setGridSize"); // Get function to stack
    lua_pushnumber(L, size);
    lua_pcall(L, 1, 0, 0);
}

void LuaBot::setAngleTurn(double angle_rotation) {
    lua_getglobal(L, "setAngleTurn"); // Get function to stack
    lua_pushnumber(L, angle_rotation);
    lua_pcall(L, 1, 0, 0);
}

void LuaBot::setGunRange(int range) {
    lua_getglobal(L, "setGunRange"); // Get function to stack
    lua_pushnumber(L, range);
    lua_pcall(L, 1, 0, 0);
}

/* UPDATERS */

void LuaBot::updateAngle(double new_angle) {
    //std::unique_lock<std::mutex> lock(m); // Por ahora no genera RC
    lua_getglobal(L, "updateAngle");
    lua_pushnumber(L, new_angle);
    lua_pcall(L, 1, 0, 0);
}

void LuaBot::cleanMap() {
    std::unique_lock<std::mutex> lock(m);
    lua_getglobal(L, "cleanMap");
    lua_pcall(L, 0, 0, 0);
}

void LuaBot::updatePosition(const Coordinate& coord) {
    std::unique_lock<std::mutex> lock(m);
    lua_getglobal(L, "updatePosition");
    lua_pushnumber(L, coord.x);
    lua_pushnumber(L, coord.y);
    lua_pcall(L, 2, 0, 0);
}

/* OTHERS */

void LuaBot::printMap() {
    lua_getglobal(L, "printMap");
    lua_pcall(L, 0, 0, 0);
}

void LuaBot::changeGun(int hotkey) {
    eventQueue.push(Event(CHANGE_GUN, id, hotkey));
    if (player.hasGun(hotkey)) {
        setGunRange(player.getGun(hotkey).getRange());
    }
}


/* LUA CALLED */

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

int LuaBot::move(lua_State *L) {
    /* Necesito sacar los 3 elementos del stack */
    int current_x = lua_tonumber(L, 1);
    int current_y = lua_tonumber(L, 2);
    double current_angle = lua_tonumber(L, 3);
    Coordinate current(current_x, current_y);
    //std::cout << "[CPP] Angle: " << current_angle << " - "; current.show();

    MovementCalculator mc;
    Coordinate new_pos = mc.moveToPosition(current, current_angle, L, 4);
    lua_pushnumber(L, new_pos.x);
    lua_pushnumber(L, new_pos.y);
    return 2;
}
