#include "server/game/map_generator.h"


MapGenerator::MapGenerator(MapParser& parser, int _max_players,
                           std::string& config_path) :
                           max_players(_max_players),
                           mapParser(parser),
                           handler(config_path) {}

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

Map MapGenerator::create() {
    Map map(max_players);
    std::unordered_map<std::string,std::vector<Coordinate>> positionables;

    positionables = getWalls();
    map.addBlockingItems(positionables, handler);

    positionables = getItems();
    map.addItems(positionables, handler);

    positionables = getPlayerSpawns();
    map.addPlayerSpawns(positionables, handler);
    return map;
}

