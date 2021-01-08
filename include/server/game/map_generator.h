#ifndef TP_WOLFENSTEIN_MAP_GENERATOR_H
#define TP_WOLFENSTEIN_MAP_GENERATOR_H

#include "map.h"
#include "map_parser.h"

class MapGenerator {
private:
    MapParser& mapParser;
public:
    MapGenerator(MapParser& parser);
    ~MapGenerator();
    Map create(int player_max_spawn_count);
    std::unordered_map<std::string,
        std::vector<Coordinate>> getWalls();
    std::unordered_map<std::string,
        std::vector<Coordinate>> getItems();
    std::unordered_map<std::string,
        std::vector<Coordinate>> getPlayerSpawns();

};

#endif //TP_WOLFENSTEIN_MAP_GENERATOR_H
