//
// Created by andy on 6/2/21.
//

#include "client/game/client_map_generator.h"

void ClientMapGenerator::create(ClientMap& map, MapParser& map_parser) {
    setMapDimensions(map, map_parser);
    addWallsToMap(map, map_parser);
    addObjectsToMap(map, map_parser);
    addPlayerSpawnsToMap(map, map_parser);
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
    int grid_size = map.getGridSize();
    std::unordered_map<std::string, std::vector<Coordinate>> objects =
            map_parser.getSpecificCategory("items");
    for (auto& object : objects) {
        int object_type = ImageManager::getImageNumberFromName(object.first);
        for (auto& coord : object.second) {
            coord.x = (coord.x * grid_size) + (int) grid_size/2;
            coord.y = (coord.y * grid_size) + (int) grid_size/2;
            map.putObjectAt(object_type, coord.x, coord.y);
        }
    }
}

void ClientMapGenerator::setMapDimensions(ClientMap& map,
                                          MapParser& map_parser) {
    Coordinate dimensions = map_parser.getDimensions();
    int width = dimensions.x;
    int height = dimensions.y;
    map.setDimensions(width, height);
}

void ClientMapGenerator::addPlayerSpawnsToMap(ClientMap& map,
                                              MapParser& map_parser) {
    int grid_size = map.getGridSize();
    std::unordered_map<std::string, std::vector<Coordinate>> spawns =
            map_parser.getSpecificCategory("players");
    for (int i = 0; i < spawns.size(); ++i) {
        for (auto& coord : spawns[std::to_string(i)]) {
            coord.x = (coord.x * grid_size) + (int) grid_size/2;
            coord.y = (coord.y * grid_size) + (int) grid_size/2;
            map.addPlayerSpawnAt(coord.x, coord.y);
        }
    }
}


