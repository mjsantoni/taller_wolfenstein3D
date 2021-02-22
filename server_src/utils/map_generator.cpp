#include "server/utils/map_generator.h"
#include "server_routes.h"

MapGenerator::MapGenerator(const std::string& map_path) :
    mapParser(MAPS_PATH_FOLDER + map_path) {}

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
