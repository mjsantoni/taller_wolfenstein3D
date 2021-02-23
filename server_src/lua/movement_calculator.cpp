#include <cmath>
#include "server/lua/movement_calculator.h"

std::vector<Coordinate>
MovementCalculator::straightLine(const Coordinate& old_pos, const Coordinate& new_pos) {
  std::vector<Coordinate> items;
  int x_old = old_pos.x;
  int y_old = old_pos.y;
  int x_new = new_pos.x;
  int y_new = new_pos.y;
  if (x_new == x_old) {
    for (int i = y_old; (y_old < y_new) ? i <= y_new : i >= y_new; (y_old < y_new) ? i++ : i--) {
      Coordinate pos(x_old, i);
      items.push_back(pos);
    }
  } else if (y_new == y_old) {
    for (int i = x_old; (x_old < x_new) ? i <= x_new : i >= x_new; (x_old < x_new) ? i++ : i--) {
      Coordinate pos(i, y_old);
      items.push_back(pos);
    }
  } else {
    bool it_on_x = abs(y_new - y_old) < abs(x_new - x_old);
    double m = (it_on_x) ? ((double) (y_new - y_old) / (x_new - x_old)) :
               ((double) (x_new - x_old) / (y_new - y_old));
    double b = (it_on_x) ? ((double) y_old - (m * x_old)) :
               ((double) x_old - (m * y_old));
    int axis_old = it_on_x ? x_old : y_old;
    int axis_new = it_on_x ? x_new : y_new;

    for (int i = axis_old; (axis_old < axis_new) ? i <= axis_new : i >= axis_new; (axis_old < axis_new) ? i++ : i--) {
      Coordinate pos(-1, -1);
      if (it_on_x) {
        pos.x = i;
        pos.y = std::round(m * i + b);
      } else {
        pos.x = std::round(m * i + b);
        pos.y = i;
      }
      items.push_back(pos);
    }
  }
  return items;
}

Coordinate
MovementCalculator::moveToPosition(const Coordinate& actual_pos, double angle, lua_State* L, int stack_position) {
  int x_move = std::round(cos(angle) * move_size);
  int y_move = std::round(sin(angle) * move_size * -1);
  int x_factor = (x_move < 0) ? -1 : 1;
  int y_factor = (y_move < 0) ? -1 : 1;
  int i = 0;
  int j = 0;
  bool is_y = abs(x_move) <= abs(y_move);
  int for_limit = (is_y) ? abs(y_move) : abs(x_move);
  int for_limit_oposite = (is_y) ? abs(x_move) : abs(y_move);
  int coord_base = (is_y) ? actual_pos.y : actual_pos.x;
  int coord_oposite = (is_y) ? actual_pos.x : actual_pos.y;
  int factor = (is_y) ? y_factor : x_factor;
  int factor_oposite = (is_y) ? x_factor : y_factor;

  for (; i < for_limit; i++) {
    int move_temp = coord_base + factor * safe_distance + factor * i;
    Coordinate new_position(-1, -1);
    if (is_y) {
      new_position.x = coord_oposite;
      new_position.y = move_temp;
    } else {
      new_position.x = move_temp;
      new_position.y = coord_oposite;
    }
    bool is_blocking = botIsABlockingItemAt(L, new_position, stack_position);
    if (!is_blocking) continue;
    else {
      i--;
      break;
    }
  }
  for (; j < for_limit_oposite && j < i; j++) {
    int move_temp = coord_oposite + factor_oposite * safe_distance + factor_oposite * j;
    Coordinate new_position(-1, -1);
    if (is_y) {
      new_position.x = move_temp;
      new_position.y = coord_base;
    } else {
      new_position.x = coord_base;
      new_position.y = move_temp;
    }
    bool is_blocking = botIsABlockingItemAt(L, new_position, stack_position);
    if (!is_blocking) continue;
    else {
      j--;
      break;
    }
  }
  Coordinate position(-1, -1);
  if (is_y) {
    position.x = actual_pos.x + j * x_factor;
    position.y = actual_pos.y + i * y_factor;
  } else {
    position.x = actual_pos.x + i * x_factor;
    position.y = actual_pos.y + j * y_factor;
  }
  return position;
}

bool MovementCalculator::botIsABlockingItemAt(lua_State* L, const Coordinate& coord, int stack_pos) {
  lua_getglobal(L, "isABlockingItemAt");
  lua_pushnumber(L, coord.x);
  lua_pushnumber(L, coord.y);
  lua_pcall(L, 2, 1, 0);
  bool is_blocking = lua_toboolean(L, stack_pos);
  lua_pop(L, 1);
  return is_blocking;
}