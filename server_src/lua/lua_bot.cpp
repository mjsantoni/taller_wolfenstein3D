#include <string>
#include <cmath>
#include "server/lua/lua_bot.h"

LuaBot::LuaBot(std::string lua_path, Player &_player, std::condition_variable &_cv, SharedQueue<Event>& eq) :
        luaEngine(lua_path),
        player(_player),
        id(player.getID()), cv(_cv), alive(true),
        eventQueue(eq) {
    setId(id);
}

LuaBot::~LuaBot() {}

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
    luaEngine.pushFunction("closestTarget");
    luaEngine.callFunction(0, 0);
}

void LuaBot::proccessEvents() {
    std::vector<int> events = getEvents();
    pushEvents(events);
}

std::vector<int> LuaBot::getEvents() {
    std::vector<int> events;
    luaEngine.getEvents(events);
    return events;
}

void LuaBot::pushEvents(std::vector<int> events) {
    for(int i = 0; i < (int) events.size(); i += 3)
        eventQueue.push(Event(events[i],events[i+1],events[i+2]));
}

void LuaBot::stop() {
    alive = false;
}


/* ADDERS API */

void LuaBot::addPositionable(Coordinate coord, std::string type) {
    std::unique_lock<std::mutex> lock(m);
    luaEngine.pushFunction("addPositionable"); // Get function to stack
    luaEngine.push(coord.x);
    luaEngine.push(coord.y);
    luaEngine.push(type);
    luaEngine.callFunction(3, 0);
}

void LuaBot::addBlocking(Coordinate coord, std::string type) {
    std::unique_lock<std::mutex> lock(m);
    luaEngine.pushFunction("addBlocking"); // Get function to stack
    luaEngine.push(coord.x);
    luaEngine.push(coord.y);
    luaEngine.push(type);
    luaEngine.callFunction(3, 0);
}

void LuaBot::addPlayer(Coordinate coord, int id) {
    std::unique_lock<std::mutex> lock(m);
    luaEngine.pushFunction("addPlayer"); // Get function to stack
    luaEngine.push(coord.x);
    luaEngine.push(coord.y);
    luaEngine.push(id);
    luaEngine.callFunction(3, 0);
}

/* SETTERS */

void LuaBot::setId(int id) {
    luaEngine.pushFunction("setId"); // Get function to stack
    luaEngine.push(id);
    luaEngine.callFunction(1, 0);
}

void LuaBot::setGridSize(int size) {
    luaEngine.pushFunction("setGridSize"); // Get function to stack
    luaEngine.push(size);
    luaEngine.callFunction(1, 0);
}

void LuaBot::setAngleTurn(double angle_rotation) {
    luaEngine.pushFunction("setAngleTurn"); // Get function to stack
    luaEngine.push(angle_rotation);
    luaEngine.callFunction(1, 0);
}

void LuaBot::setGunRange(int range) {
    luaEngine.pushFunction("setGunRange"); // Get function to stack
    luaEngine.push(range);
    luaEngine.callFunction(1, 0);
}

/* UPDATERS */

void LuaBot::cleanMap() {
    std::unique_lock<std::mutex> lock(m);
    luaEngine.pushFunction("cleanMap");
    luaEngine.callFunction(0, 0);
}

void LuaBot::updatePosition(const Coordinate& coord) {
    std::unique_lock<std::mutex> lock(m);
    luaEngine.pushFunction("updatePosition");
    luaEngine.push(coord.x);
    luaEngine.push(coord.y);
    luaEngine.callFunction(2, 0);
}

void LuaBot::sendLives(int i) {
    luaEngine.pushFunction("updateLives");
    luaEngine.push(i);
    luaEngine.callFunction(1, 0);
}
