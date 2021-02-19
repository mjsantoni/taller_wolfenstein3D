#include "server/utils/map_generator.h"

#define MAP_PATH "../ClientQT/maps/"

MapGenerator::MapGenerator(const std::string& map_path) :
                           mapParser(MAP_PATH + map_path) {}

std::unordered_map<std::string,
    std::vector<Coordinate>> MapGenerator::getWalls() {
     return mapParser.getSpecificCategory("scenarios");
}

std::unordered_map<std::string,
    std::vector<Coordinate>> MapGenerator::getItems() {
    return mapParser.getSpecificCategory("items");
}

std::unordered_map<std::string,
    std::vector<Coordinate>> MapGenerator::getPlayerSpawns() {
    return mapParser.getSpecificCategory("players");
}

MapGenerator::~MapGenerator() {}
