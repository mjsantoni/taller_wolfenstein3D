#ifndef TP_WOLFENSTEIN_COLISSION_HANDLER_H
#define TP_WOLFENSTEIN_COLISSION_HANDLER_H

#include "server/game/map.h"
#include "common/coordinate.h"

#define MOVE_SIZE 10
#define SAFE_DISTANCE 15

class ColissionHandler {
 private:
  Map& map;
  int move_size = MOVE_SIZE;
  int safe_distance = SAFE_DISTANCE;

 public:
  explicit ColissionHandler(Map& _map);
  Coordinate moveToPosition(const Coordinate& actual_pos, double angle);

  std::vector<std::pair<Coordinate, Positionable>>
  getCloseItems(const Coordinate& old_pos, const Coordinate& new_pos);

  Coordinate getCloseBlocking(const Coordinate& pos, double angle, const std::string& category);
};

#endif //TP_WOLFENSTEIN_COLISSION_HANDLER_H
