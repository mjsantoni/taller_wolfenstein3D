#ifndef TP_WOLFENSTEIN_CONFIG_PARSER_H
#define TP_WOLFENSTEIN_CONFIG_PARSER_H

#include "yaml-cpp/yaml.h"
#include <string>
#include <unordered_map>
#include <vector>

class ConfigParser {
private:

public:
    YAML::Node config;
    explicit ConfigParser(std::string path);

    /* Getters privados */
    std::unordered_map<std::string, int> getCategory(std::string node);
    std::unordered_map<std::string, std::vector<double>> getGuns();

    int getSpecificCategory(std::string category, std::string type);
    std::vector<double> getSpecificGun(std::string type);

    ~ConfigParser();
};

#endif //TP_WOLFENSTEIN_CONFIG_PARSER_H
