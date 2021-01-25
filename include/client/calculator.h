//
// Created by andy on 24/1/21.
//

#include <cmath>

#ifndef TP_WOLFENSTEIN_CALCULATOR_H
#define TP_WOLFENSTEIN_CALCULATOR_H

class Calculator {
public:
    static int calculateDelta(int delta_coord, double delta_alpha);
    static double calculateDistance(int delta_x, int delta_y);
    static double normalize(double alpha);
    static double calculateBeta(double new_angle, double original_angle);
};


#endif //TP_WOLFENSTEIN_CALCULATOR_H
