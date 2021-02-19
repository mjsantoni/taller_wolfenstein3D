#ifndef TP_WOLFENSTEIN_MAP_GENERATOR_H
#define TP_WOLFENSTEIN_MAP_GENERATOR_H

#include "server/game/map.h"
#include "common/map_parser.h"

class MapGenerator {
private:
    int max_players;
    MapParser& mapParser;
    PositionableHandler handler;

public:
    MapGenerator(MapParser& parser, int _max_players, std::string& config_path);
    ~MapGenerator();
    Map create();
    std::unordered_map<std::string,
        std::vector<Coordinate>> getWalls();
    std::unordered_map<std::string,
        std::vector<Coordinate>> getItems();
    std::unordered_map<std::string,
        std::vector<Coordinate>> getPlayerSpawns();
};

#endif //TP_WOLFENSTEIN_MAP_GENERATOR_H
