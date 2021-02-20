#include "server/game/blocking_item_handler.h"

BlockingItemHandler::BlockingItemHandler(Map &_map) :
                                        map(_map) {}

BlockingItemHandler::~BlockingItemHandler() {}

int BlockingItemHandler::openDoor(Coordinate& coordinate, Player &player) {
    Positionable item = map.getBlockingItemAt(coordinate);
    if (item.getType() == "unlocked_door" || player.useKey()) {
        std::cout << "LA LOGRE ABRIR\n";
        map.removeBlockingItemAt(coordinate);
        return item.getId();
    }
    return -1;
}

int BlockingItemHandler::pushWall(const Coordinate& coordinate) {
    if (map.getBlockingItemAt(coordinate).getType() != "fake_wall") {
        return -1;
    }
    int id = map.getBlockingItemAt(coordinate).getId();
    map.removeBlockingItemAt(coordinate);
    return id;
}



