#include "server/game/map_generator.h"


MapGenerator::MapGenerator(MapParser& parser) : mapParser(parser) {}

MapGenerator::~MapGenerator() {}


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

Map MapGenerator::create(int player_max_spawn_count, std::string _config_path) {
    Map map(player_max_spawn_count, _config_path);
    std::unordered_map<std::string,
            std::vector<Coordinate>> items = getWalls();
    map.addBlockingItems(items);
    items = getItems();
    map.addItems(items);
    items = getPlayerSpawns();
    map.addPlayerSpawns(items);


    return map;
}

