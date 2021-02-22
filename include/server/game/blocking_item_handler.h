#ifndef TP_WOLFENSTEIN_BLOCKING_ITEM_HANDLER_H
#define TP_WOLFENSTEIN_BLOCKING_ITEM_HANDLER_H

#include "server/entities/positionable.h"
#include "server/game/player.h"
#include "server/game/map.h"
#include "common/config_parser.h"
#include <queue>

class BlockingItemHandler {
 private:
  Map& map;

 public:
  explicit BlockingItemHandler(Map& _map);
  ~BlockingItemHandler();

  int openDoor(Coordinate& coordinate, Player& player);

  int pushWall(const Coordinate& coordinate);
};

#endif //TP_WOLFENSTEIN_BLOCKING_ITEM_HANDLER_H
