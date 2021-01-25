#include "server/game/config_parser.h"

#include "yaml-cpp/yaml.h"
#include <iostream>


ConfigParser::ConfigParser(std::string path) : config(YAML::LoadFile(path)) {}

ConfigParser::~ConfigParser() {}

std::unordered_map<std::string, std::vector<double>> ConfigParser::getGuns() {
    std::unordered_map<std::string, std::vector<double>> category;
    for (YAML::const_iterator it = this->config["gun"].begin(); it != this->config["gun"].end(); ++it) {
        std::vector<double> vector;
        for (YAML::const_iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            vector.push_back((*it2).as<double>());
        }
        category[it->first.as<std::string>()] = vector;
    }
    return category;
}

std::vector<double> ConfigParser::getSpecificGun(std::string type) {
    return getGuns()[type];
}

int ConfigParser::getSpecificCategory(std::string category, std::string type) {
    return getCategory(category)[type];
}

std::unordered_map<std::string, int> ConfigParser::getCategory(std::string node) {
    std::unordered_map<std::string, int> category;
    for (YAML::const_iterator it = this->config[node].begin(); it != this->config[node].end(); ++it) {
        int value = it->second.as<int>();
        category[it->first.as<std::string>()] = value;
    }
    return category;
}

