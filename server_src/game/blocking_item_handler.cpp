#include "server/game/blocking_item_handler.h"
#include "server/entities/door.h"

BlockingItemHandler::BlockingItemHandler(std::string config_path, Map& _map) :
                                        configParser(config_path),
                                        map(_map) {}

BlockingItemHandler::~BlockingItemHandler() {}

//El par es reemplazable por el int y una excepcion
std::pair<bool, int> BlockingItemHandler::openDoor(Coordinate coordinate, Player &player) {
    Positionable positionable = map.getBlockingItemAt(coordinate);
    if (positionable.getType() == "unlocked_door") {
        current_opened_doors.push(map.getNormalizedCoordinate(coordinate));
        map.removeBlockingItemAt(coordinate);
        return std::make_pair(true, -1);
    }
    int key_id = player.useKey();
    if (key_id == -1) return std::make_pair(false, -1);
    current_opened_doors.push(map.getNormalizedCoordinate(coordinate));
    map.removeBlockingItemAt(coordinate);
    return std::make_pair(true, key_id);
}



