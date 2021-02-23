#include "editor/map_exporter.h"

MapExporter::MapExporter(std::string& _width, std::string& _height,
                         std::unordered_map<std::string, std::vector<std::pair<int, int>>>& _positions) :
    width(_width), height(_height), positions(_positions) {}

YAML::Emitter& operator<<(YAML::Emitter& out, const Coordinate& coord) {
  out << YAML::Flow;
  out << YAML::BeginSeq << coord.x << coord.y << YAML::EndSeq;
  return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const std::pair<int, int>& pair) {
  out << YAML::Flow << YAML::BeginSeq << pair.first << pair.second << YAML::EndSeq;
  return out;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const std::vector<std::pair<int, int>>& v) {
  out << YAML::Flow << YAML::BeginSeq;
  for (int i = 0; i < v.size(); ++i) {
    out << v[i];
  }
  return out;
}

const char* MapExporter::getMapParsed() {
  out << YAML::BeginMap;

  out << YAML::Key << "dimensions";
  out << YAML::Value << YAML::BeginMap;
  out << YAML::Key << "width" << YAML::Value << width;
  out << YAML::Key << "height" << YAML::Value << height;
  out << YAML::EndMap;

  out << YAML::Key << "scenarios";
  out << YAML::Value << YAML::BeginMap;
  out << YAML::Key << "wood_wall";
  out << YAML::Value << positions["wood_wall"] << YAML::EndSeq;
  out << YAML::Key << "rock_wall";
  out << YAML::Value << positions["rock_wall"] << YAML::EndSeq;
  out << YAML::Key << "stone_wall";
  out << YAML::Value << positions["stone_wall"] << YAML::EndSeq;
  out << YAML::Key << "blue_wall";
  out << YAML::Value << positions["blue_wall"] << YAML::EndSeq;
  out << YAML::Key << "barrel";
  out << YAML::Value << positions["barrel"] << YAML::EndSeq;
  out << YAML::Key << "locked_door";
  out << YAML::Value << positions["locked_door"] << YAML::EndSeq;
  out << YAML::Key << "unlocked_door";
  out << YAML::Value << positions["unlocked_door"] << YAML::EndSeq;
  out << YAML::Key << "fake_wall";
  out << YAML::Value << positions["fake_wall"] << YAML::EndSeq;
  out << YAML::Key << "table";
  out << YAML::Value << positions["table"] << YAML::EndSeq;
  out << YAML::EndMap;

  out << YAML::Key << "items";
  out << YAML::Value << YAML::BeginMap;
  out << YAML::Key << "machine_gun";
  out << YAML::Value << positions["machine_gun"] << YAML::EndSeq;
  out << YAML::Key << "rpg_gun";
  out << YAML::Value << positions["rpg_gun"] << YAML::EndSeq;
  out << YAML::Key << "chain_gun";
  out << YAML::Value << positions["chain_gun"] << YAML::EndSeq;
  out << YAML::Key << "bullets";
  out << YAML::Value << positions["bullets"] << YAML::EndSeq;
  out << YAML::Key << "chest";
  out << YAML::Value << positions["chest"] << YAML::EndSeq;
  out << YAML::Key << "cross";
  out << YAML::Value << positions["cross"] << YAML::EndSeq;
  out << YAML::Key << "crown";
  out << YAML::Value << positions["crown"] << YAML::EndSeq;
  out << YAML::Key << "goblet";
  out << YAML::Value << positions["goblet"] << YAML::EndSeq;
  out << YAML::Key << "food";
  out << YAML::Value << positions["food"] << YAML::EndSeq;
  out << YAML::Key << "key";
  out << YAML::Value << positions["key"] << YAML::EndSeq;
  out << YAML::Key << "medkit";
  out << YAML::Value << positions["medkit"] << YAML::EndSeq;
  out << YAML::Key << "water_puddle";
  out << YAML::Value << positions["water_puddle"] << YAML::EndSeq;
  out << YAML::EndMap;

  out << YAML::Key << "players";
  out << YAML::Value << YAML::BeginMap;
  for (int i = 0; i < positions["player"].size(); i++) {
    out << YAML::Key << std::to_string(i);
    out << YAML::Value << YAML::Flow << YAML::BeginSeq << positions["player"][i] << YAML::EndSeq;
  }
  out << YAML::EndMap;

  out << YAML::EndMap;

  return out.c_str();
}
