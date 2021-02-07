//
// Created by andy on 24/1/21.
//

#include "client/calculator.h"

int Calculator::calculateDelta(int delta_coord, double delta_alpha) {
    return (int) (delta_coord/tan(delta_alpha));
}

double Calculator::calculateDistance(int delta_x, int delta_y) {
    //printf("val x: %d\n", delta_x);
    //printf("val y:%d\n", delta_y);
    return sqrt(pow(delta_x, 2)+pow(delta_y, 2));
}

double Calculator::normalize(double alpha) {
    if (alpha >= 2*M_PI)
        return alpha - 2*M_PI;
    if (alpha < 0)
        return alpha + 2*M_PI;
    return alpha;
}

double Calculator::calculateBeta(double new_angle, double original_angle) {
    if (std::abs(new_angle - original_angle) <= 0.523599)
        return new_angle - original_angle;
    return 2*M_PI + (new_angle - original_angle);
}

std::pair<int, int>
Calculator::calculateGrid(int grid_size, int x_pos, int y_pos) {
    int x_grid = x_pos/grid_size;
    int y_grid = y_pos/grid_size;
    return std::pair<int, int>{x_grid, y_grid};
}
