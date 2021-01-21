#ifndef TP_WOLFENSTEIN_BLOCKING_ITEM_HANDLER_H
#define TP_WOLFENSTEIN_BLOCKING_ITEM_HANDLER_H
#include "positionable.h"
#include "player.h"
#include "config_parser.h"
#include "map.h"
#include <queue>

class BlockingItemHandler {
private:
    Map& map;
    std::queue<std::pair<Coordinate, int>> current_opened_doors;

public:
    explicit BlockingItemHandler(Map &_map);
    ~BlockingItemHandler();

    std::pair<bool, int> openDoor(Coordinate coordinate, Player &player);

    bool pushWall(const Coordinate& coordinate);

    std::pair<Coordinate, int> closeDoor();
};


#endif //TP_WOLFENSTEIN_BLOCKING_ITEM_HANDLER_H
