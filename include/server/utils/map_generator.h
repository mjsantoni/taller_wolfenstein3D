#ifndef TP_WOLFENSTEIN_MAP_GENERATOR_H
#define TP_WOLFENSTEIN_MAP_GENERATOR_H

#include "common/map_parser.h"

class MapGenerator {
 private:
  MapParser mapParser;
 public:
  MapGenerator(const std::string& map_path);
  ~MapGenerator();
  std::unordered_map<std::string,
                     std::vector<Coordinate>> getWalls();
  std::unordered_map<std::string,
                     std::vector<Coordinate>> getItems();
  std::unordered_map<std::string,
                     std::vector<Coordinate>> getPlayerSpawns();
};

#endif //TP_WOLFENSTEIN_MAP_GENERATOR_H
