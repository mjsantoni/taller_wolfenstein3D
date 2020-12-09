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
    Map initializeMap();
    std::vector<std::pair<int,int>> getWalls();

};

#endif //TP_WOLFENSTEIN_MAP_GENERATOR_H
