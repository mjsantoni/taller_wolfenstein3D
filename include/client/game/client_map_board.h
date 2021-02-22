//
// Created by andy on 20/2/21.
//

#ifndef TP_WOLFENSTEIN_CLIENT_MAP_BOARD_H
#define TP_WOLFENSTEIN_CLIENT_MAP_BOARD_H

#include <utility>
#include <client/drawable.h>
#include <client/game/image_manager.h>
#include <client/calculator.h>
#include <client/object_info.h>
#include <map>

class ClientMapBoard {
 private:
  std::map<std::pair<int, int>, Drawable>& drawables_by_position;
  int grid_size;
  int width;
  int height;
  int real_width;
  int real_height;
  double max_distance;
 public:
  ClientMapBoard(int _grid_size, std::map<std::pair<int, int>, Drawable>&
  _drawables_by_position);
  bool wallAtGrid(std::pair<int, int> grid_coordinates);
  void setDimensions(int _width, int _height);

  bool wallAtGrid(int x_pos, int y_pos, int x_factor, int y_factor);
  std::pair<int, int>
  calculateGrid(int x_pos, int y_pos, int x_factor, int y_factor);
  void
  loadWallInfo(ObjectInfo& object_info, std::pair<int, int> grid_coordinates);
  void putWallAt(std::pair<int, int> coordinates, int object_type);

  void putObjectAt(int object_type, int x_pos, int y_pos);

  void updateUnlockedDoor(Drawable& door, int object_id, int x_pos,
                          int y_pos);

  void
  getMapInfoForWall(ObjectInfo& object_info, int x_pos, int y_pos,
                    int x_factor,
                    int y_factor);
};

#endif //TP_WOLFENSTEIN_CLIENT_MAP_BOARD_H
