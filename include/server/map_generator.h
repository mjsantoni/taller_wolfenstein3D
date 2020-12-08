#ifndef TP_WOLFENSTEIN_MAP_GENERATOR_H
#define TP_WOLFENSTEIN_MAP_GENERATOR_H

#include "server/map.h"
#include "server/map_parser.h"

class MapGenerator {
private:
    MapParser mapParser;
public:
    MapGenerator();
    ~MapGenerator();
    Map initializeMap();

};

#endif //TP_WOLFENSTEIN_MAP_GENERATOR_H
