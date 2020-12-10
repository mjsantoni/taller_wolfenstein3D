#include "server/map_generator.h"

MapGenerator::MapGenerator(MapParser& parser) : mapParser(parser) {}

MapGenerator::~MapGenerator() {}


std::unordered_map<std::string,
    std::vector<std::pair<int, int>>> MapGenerator::getWalls() {
     return mapParser.getSpecificCategory("scenarios");
}

std::unordered_map<std::string,
    std::vector<std::pair<int, int>>> MapGenerator::getItems() {
    return mapParser.getSpecificCategory("items");
}

std::unordered_map<std::string,
    std::vector<std::pair<int, int>>> MapGenerator::getPlayerSpawns() {
    return mapParser.getSpecificCategory("players");
}

Map MapGenerator::create() {
    Map map;
    std::unordered_map<std::string,
            std::vector<std::pair<int, int>>> items = getWalls();
    map.addBlockingItems(items);
    items = getItems();
    map.addItems(items);
    //items = getPlayerSpawns();
    //map.addPlayerSpawns(items);


    return map;
}

