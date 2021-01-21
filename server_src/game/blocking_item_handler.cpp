#include "server/game/blocking_item_handler.h"
#include "server/entities/door.h"

BlockingItemHandler::BlockingItemHandler(Map &_map) :
                                        map(_map) {}

BlockingItemHandler::~BlockingItemHandler() {}

//El par es reemplazable por el int y una excepcion
std::pair<bool, int> BlockingItemHandler::openDoor(Coordinate coordinate, Player &player) {
    Positionable item = map.getBlockingItemAt(coordinate);
    if (item.getType() == "unlocked_door") {
        std::cout << "Pusheando para guardar una puerta de id: " << item.getId() << " y "; map.getNormalizedCoordinate(coordinate).show();
        current_opened_doors.push(std::make_pair(map.getNormalizedCoordinate(coordinate), item.getId()));
        map.removeBlockingItemAt(coordinate);
        return std::make_pair(true, -1);
    }
    int key_id = player.useKey();
    if (key_id == -1) return std::make_pair(false, -1);
    std::cout << "Pusheando para guardar una puerta de id: " << item.getId() << " y "; map.getNormalizedCoordinate(coordinate).show();
    current_opened_doors.push(std::make_pair(map.getNormalizedCoordinate(coordinate), item.getId()));
    map.removeBlockingItemAt(coordinate);
    return std::make_pair(true, key_id);
}

bool BlockingItemHandler::pushWall(const Coordinate& coordinate) {
    if (map.getBlockingItemAt(coordinate).getType() != "fake_wall") {
        return false;
    }
    map.removeBlockingItemAt(coordinate);
    return true;
}

std::pair<Coordinate, int> BlockingItemHandler::closeDoor() {
    if (current_opened_doors.empty()) return std::make_pair(Coordinate(-1, -1), -1);
    std::pair<Coordinate, int> coord = current_opened_doors.front();
    current_opened_doors.pop();
    std::cout << "Cierro puerta ya unlocked de id: " << coord.second << " en "; coord.first.show();
    map.putBlockingAtExact(Door("unlocked_door", coord.second, false), coord.first);
    return coord;
}



