#ifndef TP_WOLFENSTEIN_POSITIONS_CALCULATOR_H
#define TP_WOLFENSTEIN_POSITIONS_CALCULATOR_H
#include <vector>
#include "coordinate.h"

class PositionsCalculator {
public:
    std::vector<Coordinate> straightLine(Coordinate old_pos, Coordinate new_pos);
};


#endif //TP_WOLFENSTEIN_POSITIONS_CALCULATOR_H
