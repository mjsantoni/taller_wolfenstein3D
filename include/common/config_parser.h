#ifndef TP_WOLFENSTEIN_CONFIG_PARSER_H
#define TP_WOLFENSTEIN_CONFIG_PARSER_H

#include "yaml-cpp/yaml.h"
#include <string>
#include <unordered_map>
#include <vector>

class ConfigParser {
private:
    std::unordered_map<std::string, std::vector<double>> guns;
    std::unordered_map<std::string, int> treasures;
    std::unordered_map<std::string, int> hp_items;
    std::unordered_map<std::string, int> bullets;
    std::unordered_map<std::string, int> players;

    /* Getters privados */
    std::unordered_map<std::string, int> getCategory(const std::string& node);
    std::unordered_map<std::string, std::vector<double>> getGuns();

public:
    YAML::Node config;

    explicit ConfigParser(const std::string& path);

    int getSpecificCategory(const std::string& category, const std::string& type);

    std::vector<double> getSpecificGun(const std::string& type);

    ~ConfigParser();
};

#endif //TP_WOLFENSTEIN_CONFIG_PARSER_H
