#ifndef TP_WOLFENSTEIN_MOVEMENT_CALCULATOR_H
#define TP_WOLFENSTEIN_MOVEMENT_CALCULATOR_H
#include "server/game/coordinate.h"
#include "lua_bot.h"
#include <vector>

class MovementCalculator {
private:
    int move_size = 10;
    int safe_distance = 10;
    // Ver que despues vengan por alguna especie de config y no queden hardcoded
public:
    MovementCalculator() {}
    std::vector<Coordinate> straightLine(const Coordinate& old_pos, const Coordinate& new_pos);
    Coordinate moveToPosition(const Coordinate &actual_pos, double angle, lua_State *L, int stack_position);

    bool botIsABlockingItemAt(lua_State *L, const Coordinate &coord, int stack_pos);
};


#endif //TP_WOLFENSTEIN_MOVEMENT_CALCULATOR_H
