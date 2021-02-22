#ifndef TP_WOLFENSTEIN_MAP_EXPORTER_H
#define TP_WOLFENSTEIN_MAP_EXPORTER_H

#include <string>
#include <unordered_map>
#include <vector>
#include "common/coordinate.h"
#include "yaml-cpp/yaml.h"

/* This class is the responsable of parsing the positions of all the textures*/
class MapExporter {
    std::string width;
    std::string height;
    std::unordered_map<std::string, std::vector<std::pair<int, int>>>& positions;
    YAML::Emitter out;

public:

    MapExporter(std::string &_width, std::string &_height, std::unordered_map<std::string, std::vector<std::pair<int, int>>>& _positions);

    /* Returns the char* containing all the info from the map
     * ready to load into a file*/
    const char *getMapParsed();
};


#endif //TP_WOLFENSTEIN_MAP_EXPORTER_H
