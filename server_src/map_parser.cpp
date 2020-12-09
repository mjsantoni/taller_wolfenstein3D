#include "server/map_parser.h"

#include <fstream>
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
    std::unordered_map<std::string,
        std::vector<std::pair<int, int>>> category_map = getCategory(category);
    return category_map;
}

/*
int main() {
    MapParser map_parser("../out.yaml");

    //std::pair<int, int> dimensions = map_parser.getDimensions();
    //std::unordered_map<std::string, std::vector<std::pair<int, int>>> scenarios_map = map_parser.getCategory("scenarios");
    //std::unordered_map<std::string, std::vector<std::pair<int, int>>> players_map = map_parser.getCategory("players");
    //std::unordered_map<std::string, std::vector<std::pair<int, int>>> items_map = map_parser.getCategory("items");
    //std::unordered_map<std::string, std::vector<std::pair<int, int>>> back_music_map = map_parser.getCategory("backgroundMusic");
    std::unordered_map<std::string, std::vector<std::pair<int, int>>> scenarios_map = map_parser.getSpecificCategory("scenarios");
    for (auto const& elem: scenarios_map) {
        std::cout << "Key: " << elem.first << "\n";
        for (auto const& item: elem.second) {
            std::cout << "(" << item.first << ", " << item.second << ")\n";
        }
    }
    return 0;
}
*/