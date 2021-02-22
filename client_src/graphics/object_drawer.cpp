//
// Created by andy on 4/12/20.
//

#include <algorithm>
#include "client/graphics/object_drawer.h"

bool compareByDistance(Drawable& a, Drawable& b) {
  return a.getHitDistance() > b.getHitDistance();
}

ObjectDrawer::ObjectDrawer(SdlWindow& _window,
                           ObjectInfoProvider& _object_info_provider,
                           std::map<double, double>& _wall_distance_info,
                           std::vector<double>& _angles_list,
                           ClientMap& _map,
                           TextureManager& texture_manager) :
    object_info_provider(_object_info_provider), window(_window),
    wall_distance_info(_wall_distance_info), map(_map),
    angles_list(_angles_list), drawing_assistant(window, texture_manager) {
}

std::vector<Drawable> ObjectDrawer::getMapObjects(int x, int y) {
  std::vector<Drawable> objects_vector = map.getAllDrawables();
  for (auto& object : objects_vector) {
    std::pair<int, int> object_pos = object.getMapPosition();
    double distance = Calculator::calculateDistance(x - object_pos.first,
                                                    y - object_pos.second);
    object.setHitDistance(distance);
  }
  std::sort(objects_vector.begin(), objects_vector.end(), compareByDistance);
  return objects_vector;
}

void ObjectDrawer::loadObjects(int x, int y, double player_angle) {
  std::vector<Drawable> objects_vector = getMapObjects(x, y);
  for (auto& object : objects_vector) {
    double object_starting_angle =
        getObjectAngle(x, y, object.getMapPosition());
    std::pair<int, int> object_final_pos = projectObjectOnMap(object,
                                                              player_angle);
    double object_final_angle = getObjectAngle(x, y, object_final_pos);
    double diff_angle = 0;
    if (isInsidePlayersFOV(player_angle, object_starting_angle,
                           object_final_angle, diff_angle)) {
      double x_prop = calculateObjectStartingXPos(object_starting_angle,
                                                  object_final_angle, diff_angle);
        renderObject(player_angle, object_starting_angle + diff_angle,
                     x_prop, object);
    }
  }
}

double convertToBeta(double pl_ob_angle) {
  return -pl_ob_angle;
}

void ObjectDrawer::renderObject(double player_angle, double object_angle,
                                double x_prop, Drawable &object) {
  double pl_ob_angle =
      getGammaAngle(player_angle, object_angle);
  double beta = convertToBeta(pl_ob_angle);
  if (blockedByWall(beta, object.getHitDistance(), object.getObjectType()))
    return;
  ObjectInfo object_info =
      object_info_provider.getObjectInfo(object.getObjectType());
  object_info.setHitDistance(object.getHitDistance());
  object_info.setHitGridPos(x_prop);
  //std::cout << "sprite no: " << object.getSpriteAnimationNo() << std::endl;
  object_info.setSpriteAnimationNo(object.getSpriteAnimationNo());
  drawing_assistant.put3DObject(object_info, pl_ob_angle);
}

double ObjectDrawer::calculateObjectStartingXPos(double os_angle,
                                                 double of_angle,
                                                 double diff_angle) {
  return std::abs(diff_angle / (of_angle - os_angle));
}

std::pair<int, int> ObjectDrawer::projectObjectOnMap(Drawable& object,
                                                     double player_angle) {
  double starting_fov_angle = Calculator::normalize(player_angle + 0.523599);
  std::pair<int, int> object_starting_position = object.getMapPosition();
  int object_starting_x = object_starting_position.first;
  int object_starting_y = object_starting_position.second;
  int object_width = getObjectWidth(object);
  double phi = Calculator::normalize(starting_fov_angle + 3 * M_PI / 2);
  int delta_x = (int) std::round(cos(phi) * object_width);
  int delta_y = (int) std::round(sin(phi) * object_width * -1);
  int object_final_x = object_starting_x + delta_x;
  int object_final_y = object_starting_y + delta_y;
  return std::pair<int, int>{object_final_x, object_final_y};
}

int ObjectDrawer::getObjectWidth(Drawable& drawable) {
  int object_type = drawable.getObjectType();
  ObjectInfo object_info = object_info_provider.getObjectInfo(object_type);
  return (int) (object_info.getObjectWidth() * map_grid_size);
}

bool ObjectDrawer::isInsidePlayersFOV(double player_angle,
                                      double os_angle,
                                      double of_angle,
                                      double& diff_angle) {
  double fov_starting_angle = Calculator::normalize(player_angle + 0.523599);
  double fov_finishing_angle = Calculator::normalize(player_angle - 0.523599);
  if (fov_finishing_angle >= fov_starting_angle)
    return shouldDraw_borderCase(os_angle, of_angle, fov_starting_angle,
                                 fov_finishing_angle, diff_angle);
  double sc_angle = (fov_starting_angle > fov_finishing_angle) ?
                    fov_finishing_angle : fov_starting_angle;
  double fc_angle = (fov_starting_angle > fov_finishing_angle) ?
                    fov_starting_angle : fov_finishing_angle;
  bool sa_included = (os_angle >= sc_angle && os_angle <= fc_angle);
  bool fa_included = (of_angle >= sc_angle && of_angle <= fc_angle);
  if (sa_included)
    diff_angle = 0;
  else
    diff_angle = std::abs(fc_angle - os_angle);
  return sa_included || fa_included;
}

bool ObjectDrawer::shouldDraw_borderCase(double os_angle,
                                         double of_angle,
                                         double fov_starting_angle,
                                         double fov_finishing_angle,
                                         double& diff_angle) {
  bool sa_included = (os_angle >= fov_finishing_angle ||
      os_angle <= fov_starting_angle);
  bool fa_included = (of_angle >= fov_finishing_angle ||
      of_angle <= fov_starting_angle);
  if (sa_included)
    diff_angle = 0;
  else
    diff_angle = std::abs(os_angle - fov_finishing_angle);
  return sa_included || fa_included;
}

double ObjectDrawer::getObjectAngle(int p_x, int p_y, std::pair<int, int> o_pos) {
  int o_x = o_pos.first;
  int o_y = o_pos.second;
  int delta_x = o_x - p_x;
  int delta_y = p_y - o_y;
  return Calculator::normalize(atan2(delta_y, delta_x));
}

double ObjectDrawer::getGammaAngle(double player_angle, double object_angle) {
  if (std::abs(player_angle - object_angle) <= M_PI)
    return player_angle - object_angle;
  if (player_angle > object_angle)
    return (player_angle - object_angle) - 2 * M_PI;
  return 2 * M_PI - (object_angle - player_angle);
}

bool ObjectDrawer::blockedByWall(double angle,
                                 double distance,
                                 int object_type) {
  if (object_type == EFFECT_EXPLOSION)// LOS MISILES PUEDEN EXPLOTAR EN LA PARED
      return false;
  double nearest_distance = 0;
  double angle_found = 0;
  if (wall_distance_info.find(angle) != wall_distance_info.end()) {
    nearest_distance = wall_distance_info.at(angle);
    angle_found = angle;
  } else {
    for (int i = 0; i < angles_list.size() - 1; ++i) {
      double angle_1 = angles_list[i];
      double angle_2 = angles_list[i + 1];
      if (angle_1 > angle and angle_2 < angle) {
        double diff_1 = angle_1 - angle;
        double diff_2 = angle - angle_2;
        nearest_distance = (diff_1 < diff_2) ?
                           wall_distance_info.at(angle_1) :
                           wall_distance_info.at(angle_2);
        angle_found = (diff_1 < diff_2) ? angle_1 : angle_2;
        break;
      }
    }
  }
  if (nearest_distance == 0 && angle_found == 0)
    return false;
  bool object_blocked = nearest_distance < distance;
  return object_blocked;
}

void ObjectDrawer::setDimensions(int width, int height) {
  drawing_assistant.setDimensions(width, height);
}


