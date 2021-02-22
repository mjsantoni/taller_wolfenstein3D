//
// Created by andy on 27/11/20.
//

#ifndef TP_WOLFENSTEIN_RAYCASTER_H
#define TP_WOLFENSTEIN_RAYCASTER_H

#include "client/game/client_map.h"
#include "area.h"
#include "ray_info.h"
#include "client/map_info.h"
#include "sdl_window.h"
#include "client/calculator.h"
#include "ray_caster_drawing_assistant.h"
#include "texture_manager.h"

class RayCaster {
 public:
  RayCaster(SdlWindow& window, ClientMap& map, std::map<double, double>&
  wall_distance_info, ObjectInfoProvider& info_provider,
            std::vector<double>& _angles_list, TextureManager& texture_manager);
  void renderBackground(int x, int y, double alpha);
  void setDimensions(int width, int height);
 private:
  SdlWindow window;
  ClientMap& map;
  RayCasterDrawingAssistant assistant;
  ObjectInfoProvider& info_provider;
  std::map<double, double>& wall_distance_info;
  std::vector<double>& angles_list;
  int projection_plane_width;
  double ray_angle_delta;
  void castProjectionLine(int x, int y, double alpha, double beta,
                          ObjectInfo& drawing_info);
  void castProjectionLine_vertical(int x, int y, double alpha, double beta,
                                   ObjectInfo& drawing_info);
  void castProjectionLine_vertical_up(int x, int y, double alpha,
                                      double beta, ObjectInfo& drawing_info);
  void castProjectionLine_vertical_down(int x, int y, double alpha,
                                        double beta, ObjectInfo& drawing_info);
  void castProjectionLine_horizontal(int x, int y, double alpha, double beta,
                                     ObjectInfo& drawing_info);
  void castProjectionLine_horizontal_right(int x, int y, double alpha,
                                           double beta, ObjectInfo& drawing_info);
  void castProjectionLine_horizontal_left(int x, int y, double alpha,
                                          double beta, ObjectInfo& drawing_info);
  bool outOfBounds(ClientMap& map, int x_pos, bool is_vertical);
  void fillRayInfo(double beta, int x_pos, int y_pos, int delta_x,
                   int delta_y, ObjectInfo& object_info, int x_factor,
                   int y_factor);
  ObjectInfo fillObjectInfo(ObjectInfo& map_info);
  int calculateBorderFactor(bool should_decrease, int position);
  void saveRayInformation(double ray_angle, double distance);
};

#endif //TP_WOLFENSTEIN_RAYCASTER_H
