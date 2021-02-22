//
// Created by andy on 24/1/21.
//

#include "client/calculator.h"

#define HALF_FOV_RAD 0.523599

int Calculator::calculateDelta(int delta_coord, double delta_alpha) {
  return (int) (delta_coord / tan(delta_alpha));
}

double Calculator::calculateDistance(int delta_x, int delta_y) {
  //printf("val x: %d\n", delta_x);
  //printf("val y:%d\n", delta_y);
  return sqrt(pow(delta_x, 2) + pow(delta_y, 2));
}

double Calculator::normalize(double angle) {
  if (angle >= 2 * M_PI)
    return angle - 2 * M_PI;
  if (angle < 0)
    return angle + 2 * M_PI;
  return angle;
}

double Calculator::calculateBeta(double new_angle, double alpha) {
  if (std::abs(new_angle - alpha) <= HALF_FOV_RAD)
    return new_angle - alpha;
  return 2 * M_PI + (new_angle - alpha);
}

std::pair<int, int>
Calculator::calculateGrid(int grid_size, int x_pos, int y_pos) {
  int x_grid = x_pos / grid_size;
  int y_grid = y_pos / grid_size;
  return std::pair<int, int>{x_grid, y_grid};
}
