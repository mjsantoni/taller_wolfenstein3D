#include "common/map_parser.h"
#include <iostream>

MapParser::MapParser(const std::string& path) : config(YAML::LoadFile(path)) {
  items = getCategory("items");
  players = getCategory("players");
  scenarios = getCategory("scenarios");
}

MapParser::~MapParser() {}

std::unordered_map<std::string, std::vector<Coordinate>> MapParser::getCategory(const std::string& node) {
  std::unordered_map<std::string, std::vector<Coordinate>> category;
  for (YAML::const_iterator it = this->config[node].begin(); it != this->config[node].end(); ++it) {
    std::vector<Coordinate> vector;
    for (YAML::const_iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
      vector.emplace_back((*it2)[0].as<int>(), (*it2)[1].as<int>());
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
                   std::vector<Coordinate>> MapParser::getSpecificCategory(const std::string& category) {
  if (category == "items") return items;
  else if (category == "players") return players;
  else if (category == "scenarios") return scenarios;
  else return getCategory(category);
}