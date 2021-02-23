//
// Created by andy on 4/12/20.
//

#ifndef TP_WOLFENSTEIN_OBJECTDRAWER_H
#define TP_WOLFENSTEIN_OBJECTDRAWER_H

#include <vector>
#include <zconf.h>
#include <map>
#include <limits>
#include "image_parser.h"
#include "sdl_window.h"
#include "image_info.h"
#include "client/calculator.h"
#include "client/game/client_map.h"
#include "object_drawing_assistant.h"
#include "texture_manager.h"

class ObjectDrawer {
 private:
  SdlWindow& window;
  ObjectInfoProvider& object_info_provider;
  int map_grid_size = 64;
  std::map<double, double>& wall_distance_info;
  std::vector<double>& angles_list;
  ClientMap& map;
  ObjectDrawingAssistant drawing_assistant;
  bool isInsidePlayersFOV(double player_angle, double os_angle, double of_angle,
                          double& diff_angle);
  bool shouldDraw_borderCase(double os_angle, double of_angle,
                             double fov_starting_angle,
                             double fov_finishing_angle, double& diff_angle);
  double getObjectAngle(int p_x, int p_y, std::pair<int, int> o_pos);
  std::pair<int, int> projectObjectOnMap(Drawable& object,
                                         double player_angle);
  double calculateObjectStartingXPos(double os_angle, double of_angle,
                                     double diff_angle);
  void renderObject(double player_angle, double object_angle,
                    double x_prop, Drawable& object);
  double getGammaAngle(double player_angle, double object_angle);
  bool blockedByWall(double angle, double distance, int object_type);
  std::vector<Drawable> getMapObjects(int x, int y);
 public:
  ObjectDrawer(SdlWindow& _window, ObjectInfoProvider& object_info_provider,
               std::map<double, double>& wall_distance_info,
               std::vector<double>& angles_list, ClientMap& map,
               TextureManager& texture_manager);
  void loadObjects(int x, int y, double player_angle);
  void setDimensions(int width, int height);
  int getObjectWidth(Drawable& drawable);
};

#endif //TP_WOLFENSTEIN_OBJECTDRAWER_H