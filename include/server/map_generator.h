#ifndef TP_WOLFENSTEIN_MAP_GENERATOR_H
#define TP_WOLFENSTEIN_MAP_GENERATOR_H

#include "server/map.h"
#include "server/map_parser.h"

class MapGenerator {
private:
    MapParser& mapParser;
public:
    MapGenerator(MapParser& parser);
    ~MapGenerator();
    Map create();
    std::unordered_map<std::string,
        std::vector<std::pair<int, int>>> getWalls();
    std::unordered_map<std::string,
        std::vector<std::pair<int, int>>> getItems();
    std::unordered_map<std::string,
        std::vector<std::pair<int, int>>> getPlayerSpawns();

};

#endif //TP_WOLFENSTEIN_MAP_GENERATOR_H
