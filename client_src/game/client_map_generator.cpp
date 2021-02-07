//
// Created by andy on 6/2/21.
//

#include "client/game/client_map_generator.h"

void ClientMapGenerator::create(ClientMap& map, MapParser& map_parser) {
    addWallsToMap(map, map_parser);
    addObjectsToMap(map, map_parser);
}

void ClientMapGenerator::addWallsToMap(ClientMap& map, MapParser& map_parser) {
    std::unordered_map<std::string, std::vector<Coordinate>> walls =
            map_parser.getSpecificCategory("scenarios");
    for (auto& wall : walls) {
        int object_type = ImageManager::getImageNumberFromName(wall.first);
        for (auto& coord : wall.second) {
            int x_pos = coord.x;
            int y_pos = coord.y;
            map.putDrawableAt(std::pair<int, int>{x_pos, y_pos}, object_type);
        }
    }
}

void ClientMapGenerator::addObjectsToMap(ClientMap& map, MapParser& map_parser){
    std::unordered_map<std::string, std::vector<Coordinate>> walls =
            map_parser.getSpecificCategory("scenarios");
    for (auto& wall : walls) {
        int object_type = ImageManager::getImageNumberFromName(wall.first);
        for (auto& coord : wall.second) {
            int x_pos = coord.x;
            int y_pos = coord.y;
            map.putDrawableAt(x_pos, y_pos, object_type);
        }
    }
}


