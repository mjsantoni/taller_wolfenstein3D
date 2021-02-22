#include "common/config_parser.h"

ConfigParser::ConfigParser(const std::string& path) : config(YAML::LoadFile(path)) {
  hp_items = getCategory("hp_item");
  bullets = getCategory("bullets");
  treasures = getCategory("treasure");
  guns = getGuns();
  players = getCategory("player");
}

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

std::vector<double> ConfigParser::getSpecificGun(const std::string& type) {
  return guns[type];
}

int ConfigParser::getSpecificCategory(const std::string& category, const std::string& type) {
  if (category == "treasure") return treasures[type];
  else if (category == "hp_item") return hp_items[type];
  else if (category == "bullets") return bullets[type];
  else if (category == "player") return players[type];
  else return -1; // Aca pusiste algo que no existe
}

std::unordered_map<std::string, int> ConfigParser::getCategory(const std::string& node) {
  std::unordered_map<std::string, int> category;
  for (YAML::const_iterator it = this->config[node].begin(); it != this->config[node].end(); ++it) {
    int value = it->second.as<int>();
    category[it->first.as<std::string>()] = value;
  }
  return category;
}

std::pair<int, int> ConfigParser::getResolution() {
  return std::make_pair(this->config["resolution"]["weapon_width"].as<int>(),
                        this->config["resolution"]["height"].as<int>());
}

