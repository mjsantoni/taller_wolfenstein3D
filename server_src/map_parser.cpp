#include "server/map_parser.h"
#include "yaml-cpp/yaml.h"
#include <iostream>

MapParser::MapParser(std::string path) : config(YAML::LoadFile(path)) {}

MapParser::~MapParser() {}

std::unordered_map<std::string, std::vector<std::pair<int, int>>> MapParser::getCategory(std::string node) {
    std::unordered_map<std::string, std::vector<std::pair<int, int>>> category;
    for (YAML::const_iterator it = this->config[node].begin(); it != this->config[node].end(); ++it) {
        std::vector<std::pair<int, int>> vector;
        for (YAML::const_iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            vector.push_back(std::pair<int, int>((*it2)[0].as<int>(), (*it2)[1].as<int>()));
        }
        category[it->first.as<std::string>()] = vector;
    }
    return category;
}

std::pair<int, int> MapParser::getDimensions() {
    std::pair<int, int> dimensions(this->config["dimensions"]["width"].as<int>(), this->config["dimensions"]["height"].as<int>());
    return dimensions;
}

std::unordered_map<std::string,
    std::vector<std::pair<int, int>>> MapParser::getSpecificCategory(std::string category) {
    return getCategory(category);
}