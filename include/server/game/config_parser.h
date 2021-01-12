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

    std::unordered_map<std::string, int> getCategory(std::string node);
    std::unordered_map<std::string, int> getSpecificCategory(std::string category);
    std::unordered_map<std::string, std::vector<double>> getGuns();

    ~ConfigParser();

    int getBullets();
};


#endif //TP_WOLFENSTEIN_CONFIG_PARSER_H
