#ifndef TP_WOLFENSTEIN_MAPPARSER_H
#define TP_WOLFENSTEIN_MAPPARSER_H


#include "yaml-cpp/yaml.h"
#include <string>
#include <unordered_map>

class MapParser {
    private:


    public:
        YAML::Node config;
        explicit MapParser(std::string path);

        std::unordered_map<std::string, std::vector<std::pair<int, int>>> getCategory(std::string node);
        std::pair<int, int> getDimensions();

        ~MapParser();
};


#endif //TP_WOLFENSTEIN_MAPPARSER_H
