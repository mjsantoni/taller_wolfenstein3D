#include "server/map_generator.h"

MapGenerator::MapGenerator(MapParser& parser) : mapParser(parser) {}

MapGenerator::~MapGenerator() {}


std::vector<std::pair<int,int>> MapGenerator::getWalls() {

     return mapParser.getSpecificCategory("scenarios")["walls"];
}