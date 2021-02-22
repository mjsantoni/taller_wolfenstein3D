//
// Created by andy on 2/12/20.
//

#ifndef TP_WOLFENSTEIN_RAYINFO_H
#define TP_WOLFENSTEIN_RAYINFO_H

class RayInfo {
 public:
  int vertical_hit_x = 0;
  int vertical_hit_y = 0;
  int horizontal_hit_x = 0;
  int horizontal_hit_y = 0;
  double vertical_distance = 0;
  double horizontal_distance = 0;
  int vertical_object_type = 0;
  int horizontal_object_type = 0;
  int vertical_grid_pos = 0;
  int horizontal_grid_pos = 0;
  double distance = 0;
  int hit_x = 0;
  int hit_y = 0;
  int grid_pos = 0;
  int object_type = 0;
};

#endif //TP_WOLFENSTEIN_RAYINFO_H
