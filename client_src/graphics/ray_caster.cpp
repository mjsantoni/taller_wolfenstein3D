//
// Created by andy on 27/11/20.
//

#include "client/graphics/ray_caster.h"

#include <thread>

#define HALF_FOV_RAD 0.523599
#define FOV_ANGLE 60
#define GRID_SIZE 64

RayCaster::RayCaster(SdlWindow& window,
                     ClientMap& map,
                     std::map<double, double>& _wall_distance_info,
                     ObjectInfoProvider& _info_provider,
                     std::vector<double>& _angles_list,
                     TextureManager& texture_manager) :
    window(window), wall_distance_info(_wall_distance_info), map(map),
    info_provider(_info_provider), angles_list(_angles_list),
    assistant(window, texture_manager) {
}

void RayCaster::renderBackground(int x, int y, double alpha) {
  double angle = Calculator::normalize(alpha + HALF_FOV_RAD);
  for (int ray = 0; ray < projection_plane_width; ++ray) {
    RayInfo ray_info{};
    double beta = Calculator::calculateBeta(angle, alpha);
    castProjectionLine(x, y, angle, beta, ray_info);
    ObjectInfo object_info = fillObjectInfo(ray_info);
    assistant.putFloorAndCeiling(ray, object_info);
    assistant.putWall(ray, object_info);
    angle -= ray_angle_delta;
    if (angle < 0) {
      angle += 2 * M_PI;
      alpha += 2 * M_PI;
    }
  }
}

ObjectInfo RayCaster::fillObjectInfo(RayInfo& ray_info) {
  ObjectInfo object_info =
      info_provider.getObjectInfo(ray_info.getObjectType());
  object_info.setHitDistance(ray_info.getHitDistance());
  object_info.setHitGridPos(ray_info.getHitGridPosition());
  return object_info;
}

void RayCaster::castProjectionLine(int x,
                                   int y,
                                   double alpha,
                                   double beta,
                                   RayInfo& ray_info) {
  castProjectionLine_vertical(x, y, alpha, beta, ray_info);
  castProjectionLine_horizontal(x, y, alpha, beta, ray_info);
  saveRayInformation(beta, ray_info.getHitDistance());
}

void RayCaster::castProjectionLine_vertical(int x,
                                            int y,
                                            double alpha,
                                            double beta,
                                            RayInfo& ray_info) {
  if (alpha <= M_PI)
    return castProjectionLine_vertical_up(x, y, alpha, beta, ray_info);
  return castProjectionLine_vertical_down(x, y, alpha, beta, ray_info);
}

void RayCaster::castProjectionLine_horizontal(int x,
                                              int y,
                                              double alpha,
                                              double beta,
                                              RayInfo& ray_info) {
  if (alpha >= M_PI / 2 && alpha <= 3 * M_PI / 2)
    return castProjectionLine_horizontal_left(x, y, alpha, beta, ray_info);
  return castProjectionLine_horizontal_right(x, y, alpha, beta, ray_info);
}

void RayCaster::castProjectionLine_vertical_up(int x,
                                               int y,
                                               double alpha,
                                               double beta,
                                               RayInfo& ray_info) {
  int delta_y = y % map.getGridSize();
  double lambda = (alpha > M_PI / 2) ? M_PI - alpha : alpha;
  bool ray_pointing_left = alpha >= M_PI / 2;
  int x_inverter = (ray_pointing_left) ? -1 : 1;
  while (true) {
    int delta_x = Calculator::calculateDelta(delta_y, lambda) * x_inverter;
    if (outOfBounds(y - delta_y, true))
      return;

    int x_factor = calculateBorderFactor(ray_pointing_left, x + delta_x);
    if (map.wallAtGrid(x + delta_x, y - delta_y, x_factor, -1)) {
      fillRayInfo(beta, x, y, delta_x, -delta_y, ray_info, x_factor, -1);
      return;
    }
    delta_y += map.getGridSize();
  }
}

void RayCaster::castProjectionLine_vertical_down(int x,
                                                 int y,
                                                 double alpha,
                                                 double beta,
                                                 RayInfo& ray_info) {
  int delta_y = map.getGridSize() - y % map.getGridSize();
  double lambda = (alpha <= 3 * M_PI / 2) ? alpha - M_PI : 2 * M_PI - alpha;
  bool ray_pointing_right = alpha <= 3 * M_PI / 2;
  int x_inverter = (ray_pointing_right) ? -1 : 1;
  while (true) {
    int delta_x = Calculator::calculateDelta(delta_y, lambda) * x_inverter;
    if (outOfBounds(y + delta_y, true))
      return;

    int x_factor = calculateBorderFactor(ray_pointing_right, x + delta_x);
    if (map.wallAtGrid(x + delta_x, y + delta_y, x_factor, 0)) {
      fillRayInfo(beta, x, y, delta_x, delta_y, ray_info, x_factor, 0);
      return;
    }
    delta_y += map.getGridSize();
  }
}

void RayCaster::castProjectionLine_horizontal_left(int x,
                                                   int y,
                                                   double alpha,
                                                   double beta,
                                                   RayInfo& ray_info) {
  int delta_x = x % map.getGridSize();
  double lambda = (alpha <= M_PI) ? alpha - M_PI / 2 : 3 * M_PI / 2 - alpha;
  bool ray_pointing_up = alpha <= M_PI;
  int y_inverter = (ray_pointing_up) ? -1 : 1;

  while (true) {
    int delta_y = Calculator::calculateDelta(delta_x, lambda) * y_inverter;
    if (outOfBounds(x - delta_x, false))
      return;

    int y_factor = calculateBorderFactor(ray_pointing_up, y + delta_y);
    if (map.wallAtGrid(x - delta_x, y + delta_y, -1, y_factor)) {
      fillRayInfo(beta, x, y, -delta_x, delta_y, ray_info, -1, y_factor);
      return;
    }
    delta_x += map.getGridSize();
  }
}

void RayCaster::castProjectionLine_horizontal_right(int x,
                                                    int y,
                                                    double alpha,
                                                    double beta,
                                                    RayInfo& ray_info) {
  int delta_x = map.getGridSize() - x % map.getGridSize();
  double lambda = (alpha <= M_PI / 2) ? M_PI / 2 - alpha : alpha -
      3 * M_PI / 2;
  bool ray_pointing_up = alpha <= M_PI;
  int y_inverter = (ray_pointing_up) ? -1 : 1;
  while (true) {
    int delta_y = Calculator::calculateDelta(delta_x, lambda) * y_inverter;
    if (outOfBounds(x + delta_x, false))
      return;

    int y_factor = calculateBorderFactor(ray_pointing_up, y + delta_y);
    if (map.wallAtGrid(x + delta_x, y + delta_y, 0, y_factor)) {
      fillRayInfo(beta, x, y, delta_x, delta_y, ray_info, 0, y_factor);
      return;
    }
    delta_x += map.getGridSize();
  }
}

bool RayCaster::outOfBounds(int pos, bool is_vertical) {
  if (is_vertical)
    return map.outOfVerticalBounds(pos);
  return map.outOfHorizontalBounds(pos);
}

void RayCaster::fillRayInfo(double beta,
                            int x_pos,
                            int y_pos,
                            int delta_x,
                            int delta_y,
                            RayInfo& ray_info,
                            int x_factor,
                            int y_factor) {
  double final_distance = Calculator::calculateDistance(delta_x, delta_y)
      * cos(beta);
  if (final_distance >= ray_info.getHitDistance()
                                            && ray_info.getHitDistance() != 0)
    return;
  ray_info.setHitDistance(final_distance);
  map.getMapInfoForWall(ray_info, x_pos + delta_x, y_pos + delta_y,
                        x_factor, y_factor);
  double hit_grid_pos = ((x_pos + delta_x) % GRID_SIZE == 0) ?
                        double((y_pos + delta_y) % GRID_SIZE) / GRID_SIZE :
                        double((x_pos + delta_x) % GRID_SIZE) / GRID_SIZE;
   ray_info.setHitGridPosition(hit_grid_pos);
}

int RayCaster::calculateBorderFactor(bool should_decrease, int position) {
  if (!should_decrease || position % map.getGridSize() != 0)
    return 0;
  return -1;
}

void RayCaster::saveRayInformation(double ray_angle, double distance) {
  wall_distance_info.insert(std::pair<double, double>(ray_angle, distance));
  angles_list.push_back(ray_angle);
}

void RayCaster::setDimensions(int width, int height) {
  projection_plane_width = width;
  ray_angle_delta = (double) (double(FOV) / projection_plane_width * M_PI / 180);
  assistant.setDimensions(width, height);
}