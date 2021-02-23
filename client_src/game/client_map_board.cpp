//
// Created by andy on 20/2/21.
//


#include "client/game/client_map_board.h"

ClientMapBoard::ClientMapBoard(int _grid_size,
                               std::map<std::pair<int, int>, Drawable>& _drawables_by_position) :
    drawables_by_position(_drawables_by_position) {
  grid_size = _grid_size;
}

bool ClientMapBoard::wallAtGrid(std::pair<int, int> grid_coordinates) {
  int x_pos = grid_coordinates.first;
  int y_pos = grid_coordinates.second;
  if (x_pos < 0)
    x_pos = 0;
  if (y_pos < 0)
    y_pos = 0;
  x_pos *= grid_size;
  y_pos *= grid_size;
  std::pair<int, int> coordinates(x_pos, y_pos);
  if (drawables_by_position.find(coordinates) == drawables_by_position.end())
    return false;
  Drawable& drawable = drawables_by_position.at(coordinates);
  int object_type = drawable.getObjectType();
  return ImageManager::objectIsWall(object_type);
}

std::pair<int, int> ClientMapBoard::calculateGrid(int x_pos,
                                                  int y_pos,
                                                  int x_factor,
                                                  int y_factor) {
  if (x_pos < 0 || y_pos < 0)
    return {-1, -1};
  int x_grid = x_pos / grid_size + x_factor;
  int y_grid = y_pos / grid_size + y_factor;
  return {x_grid, y_grid};
}

bool ClientMapBoard::wallAtGrid(int x_pos,
                                int y_pos,
                                int x_factor,
                                int y_factor) {
  if (x_pos < 0 || y_pos < 0 || x_pos > real_width || y_pos > real_height)
    return false;
  std::pair<int, int> grid_coordinates =
      calculateGrid(x_pos, y_pos, x_factor, y_factor);
  bool wall_at_grid = wallAtGrid(grid_coordinates);
  return wall_at_grid;
}

void ClientMapBoard::setDimensions(int _width, int _height) {
  width = _width;
  height = _height;
  real_width = width * grid_size;
  real_height = height * grid_size;
  max_distance = Calculator::calculateDistance(real_width, real_height);
}

void ClientMapBoard::loadWallInfo(RayInfo& ray_info,
                                  std::pair<int, int> grid_coordinates) {
  Drawable drawable = drawables_by_position.at(grid_coordinates);
  ray_info.setObjectType(drawable.getObjectType());
  ray_info.setMapStartingPosition(drawable.getMapPosition());
}

void ClientMapBoard::putWallAt(std::pair<int, int> coordinates,
                               int object_type) {
  Drawable drawable(object_type);
  coordinates.first *= grid_size;
  coordinates.second *= grid_size;
  drawables_by_position.insert(std::pair<std::pair<int, int>,
                                         Drawable>(coordinates, drawable));
}

void ClientMapBoard::putObjectAt(int object_type, int x_pos, int y_pos) {
  Drawable drawable(object_type);
  drawable.setMapPosition(x_pos, y_pos);
  std::pair<int, int> coords{x_pos, y_pos};
  drawables_by_position.insert(std::pair<std::pair<int, int>,
                                         Drawable>(coords, drawable));
}

void ClientMapBoard::updateUnlockedDoor(Drawable& door,
                                        int object_id,
                                        int x_pos,
                                        int y_pos) {
  door.setId(object_id);
  door.setMapPosition(x_pos, y_pos);
  std::pair<int, int> map_pos{x_pos, y_pos};
  drawables_by_position.insert(std::pair<std::pair<int, int>, Drawable>
                                   (map_pos, door));
}

void ClientMapBoard::getMapInfoForWall(RayInfo& ray_info,
                                       int x_pos,
                                       int y_pos,
                                       int x_factor,
                                       int y_factor) {

  int x_coord = x_pos / grid_size * grid_size + x_factor * grid_size;
  int y_coord = y_pos / grid_size * grid_size + y_factor * grid_size;
  if (x_coord < 0)
    x_coord = 0;
  if (y_coord < 0)
    y_coord = 0;
  std::pair<int, int> grid_coordinates{x_coord, y_coord};
  if (wallAtGrid(x_pos, y_pos, x_factor, y_factor))
    loadWallInfo(ray_info, grid_coordinates);
}
