#include "server/lua/lua_engine.h"

LuaEngine::LuaEngine(std::string& path) : L(luaL_newstate()) {
  luaL_openlibs(L);
  luaL_dofile(L, path.c_str());
  lua_register(L, "isInSight", isInSight);
  lua_register(L, "move", move);
}

LuaEngine::~LuaEngine() { lua_close(L); }

void LuaEngine::pushFunction(std::string func) { lua_getglobal(L, func.c_str()); }
void LuaEngine::push(std::string& value) { lua_pushstring(L, value.c_str()); }
void LuaEngine::push(int value) { lua_pushnumber(L, value); }
void LuaEngine::push(double value) { lua_pushnumber(L, value); }
void LuaEngine::pushTable(int value) { lua_pushvalue(L, value); }
void LuaEngine::pushNill() { lua_pushnil(L); }
void LuaEngine::callFunction(int recv, int back) { lua_pcall(L, recv, back, 0); }

void LuaEngine::getEvents(std::vector<int>& events) {
  lua_getglobal(L, "getEvents");
  lua_pcall(L, 0, 1, 0);
  lua_pushvalue(L, -1);
  lua_pushnil(L);
  while (lua_next(L, -2)) {
    events.push_back(lua_tonumber(L, -1));
    lua_pop(L, 1);
  }
  lua_pop(L, 1);
}

/* LUA CALLED */

bool LuaEngine::isABlockingItemAt(lua_State* L, const Coordinate& coord, int stack_pos) {
  lua_getglobal(L, "isABlockingItemAt");
  lua_pushnumber(L, coord.x);
  lua_pushnumber(L, coord.y);
  lua_pcall(L, 2, 1, 0);
  bool is_blocking = lua_toboolean(L, stack_pos);
  lua_pop(L, 1);
  return is_blocking;
}

int LuaEngine::isInSight(lua_State* L) {
  /* Necesito sacar los 4 elementos del stack */
  int x_old = lua_tonumber(L, 1);
  int y_old = lua_tonumber(L, 2);
  int x_new = lua_tonumber(L, 3);
  int y_new = lua_tonumber(L, 4);

  Coordinate actual(x_old, y_old);
  Coordinate future(x_new, y_new);
  MovementCalculator mc;
  std::vector<Coordinate> path = mc.straightLine(actual, future);
  for (auto& coord : path) {
    bool is_blocking = isABlockingItemAt(L, coord, 5);
    if (is_blocking) {
      lua_pushnumber(L, 0); // Cargo un 0 para indicar que encontre un blocking
      return 1;
    }
  }
  lua_pushnumber(L, 1); // No hay paredes en el medio
  return 1;
}

int LuaEngine::move(lua_State* L) {
  /* Necesito sacar los 3 elementos del stack */
  int current_x = lua_tonumber(L, 1);
  int current_y = lua_tonumber(L, 2);
  double current_angle = lua_tonumber(L, 3);
  Coordinate current(current_x, current_y);

  MovementCalculator mc;
  Coordinate new_pos = mc.moveToPosition(current, current_angle, L, 4);
  lua_pushnumber(L, new_pos.x);
  lua_pushnumber(L, new_pos.y);
  return 2;
}