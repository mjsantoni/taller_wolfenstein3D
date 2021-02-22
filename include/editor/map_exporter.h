#ifndef TP_WOLFENSTEIN_MAP_EXPORTER_H
#define TP_WOLFENSTEIN_MAP_EXPORTER_H

#include <string>
#include <unordered_map>
#include <vector>
#include "common/coordinate.h"
#include "yaml-cpp/yaml.h"

class MapExporter {
    std::string width;
    std::string height;
    std::unordered_map<std::string, std::vector<std::pair<int, int>>>& positions;
    YAML::Emitter out;
public:
    MapExporter(std::string &_width, std::string &_height, std::unordered_map<std::string, std::vector<std::pair<int, int>>>& _positions);
    const char *getMapParsed();
};


#endif //TP_WOLFENSTEIN_MAP_EXPORTER_H
