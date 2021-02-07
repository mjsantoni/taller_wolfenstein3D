#include "common/map_parser.h"
#include "yaml-cpp/yaml.h"
#include <iostream>


MapParser::MapParser(std::string path) : config(YAML::LoadFile(path)) {}

MapParser::~MapParser() {}

std::unordered_map<std::string, std::vector<Coordinate>> MapParser::getCategory(std::string node) {
    std::unordered_map<std::string, std::vector<Coordinate>> category;
    for (YAML::const_iterator it = this->config[node].begin(); it != this->config[node].end(); ++it) {
        std::vector<Coordinate> vector;
        for (YAML::const_iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            vector.push_back(Coordinate((*it2)[0].as<int>(), (*it2)[1].as<int>()));
        }
        category[it->first.as<std::string>()] = vector;
    }
    return category;
}

Coordinate MapParser::getDimensions() {
    Coordinate dimensions(this->config["dimensions"]["width"].as<int>(), this->config["dimensions"]["height"].as<int>());
    return dimensions;
}

std::unordered_map<std::string,
    std::vector<Coordinate>> MapParser::getSpecificCategory(std::string category) {
    return getCategory(category);
}