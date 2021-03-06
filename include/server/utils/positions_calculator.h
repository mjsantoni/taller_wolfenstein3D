#ifndef TP_WOLFENSTEIN_POSITIONS_CALCULATOR_H
#define TP_WOLFENSTEIN_POSITIONS_CALCULATOR_H

#include "common/coordinate.h"
#include <vector>

class PositionsCalculator {
 public:
  /* Dada dos posiciones devuelve la linea recta que une ambos puntos */
  std::vector<Coordinate> straightLine(const Coordinate& old_pos,
                                       const Coordinate& new_pos);
};

#endif //TP_WOLFENSTEIN_POSITIONS_CALCULATOR_H
