//
// Created by andy on 24/1/21.
//

#include <cmath>
#include <utility>

#ifndef TP_WOLFENSTEIN_CALCULATOR_H
#define TP_WOLFENSTEIN_CALCULATOR_H

class Calculator {
public:
    static int calculateDelta(int delta_coord, double delta_alpha);
    static double calculateDistance(int delta_x, int delta_y);
    static double normalize(double alpha);
    static double calculateBeta(double new_angle, double original_angle);
    static std::pair<int, int> calculateGrid(int grid_size, int x_pos,
                                             int y_pos);
};


#endif //TP_WOLFENSTEIN_CALCULATOR_H
