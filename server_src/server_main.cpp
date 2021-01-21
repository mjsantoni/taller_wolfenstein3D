#include "server/game/game.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include "server/game/config_parser.h"
#include <string>
#include <unordered_map>
#include <vector>

int main( int argc, char* args[] ) {
    Game game("../map.yaml", "../config.yaml");
    //game.show();
    game.rotate(1, 3*M_PI/8);
    game.rotate(0, 3*M_PI/8);
    game.movePlayer(1);
    game.show();
    game.shoot(0);
    //game.shoot(0);
    //game.shoot(0);
    //game.shoot(0);

    //game.addBulletsTo(0, 5);
    //game.movePlayer(1);
    //game.movePlayer(1);
    //game.movePlayer(1);
    //game.movePlayer(0);
    //game.movePlayer(0);
    //game.movePlayer(0);
    //game.movePlayer(0);
    //game.movePlayer(0);
    //game.movePlayer(0);
    //game.openDoor(0);
    //game.rotate(0,7*M_PI/4);
    //game.movePlayer(0);
    //game.movePlayer(0,7*M_PI/4);

    //game.shoot(0);
    game.show();
    game.movePlayer(0);
    //game.closeDoor();
    game.show();
    return 0;

}
/*
int main(int argc, char* args[]) {
    ConfigParser cp("../config.yaml");
    //std::unordered_map<std::string, std::vector<double>> vect = cp.getGuns();
    std::unordered_map<std::string, int> vect = cp.getSpecificCategory("treasure");
    for (auto& elem : vect) {
        std::cout << "Key: " << elem.first << " - Value: " << elem.second << "\n";
    }
    std::cout << "Bullets: " << cp.getBullets() << "\n";
}*/

/* GENERADOR DEL CONFIG.YAML */ /*
#include "yaml-cpp/yaml.h"
int main() {
    YAML::Emitter out;
    out << YAML::BeginMap;

    out << YAML::Key << "hp_items";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "blood_puddle" << YAML::Value << 1;
    out << YAML::Key << "food" << YAML::Value << 10;
    out << YAML::Key << "medkit" << YAML::Value << 20;
    out << YAML::EndMap;

    out << YAML::Key << "bullets" << YAML::Value << 5;

    out << YAML::Key << "treasure";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "cross" << YAML::Value << 10;
    out << YAML::Key << "goblet" << YAML::Value << 50;
    out << YAML::Key << "chest" << YAML::Value << 100;
    out << YAML::Key << "crown" << YAML::Value << 200;
    out << YAML::EndMap;

    out << YAML::Key << "gun";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "chain_gun";
    out << YAML::Value << YAML::Flow << YAML::BeginSeq << 1 << 0.1 << 0.8 << YAML::EndSeq;
    out << YAML::Key << "machine_gun";
    out << YAML::Value << YAML::Flow << YAML::BeginSeq << 5 << 0.3 << 0.6 << YAML::EndSeq;
    out << YAML::Key << "rpg_gun";
    out << YAML::Value << YAML::Flow << YAML::BeginSeq << 5 << 1 << 1 << YAML::EndSeq;
    out << YAML::EndMap;

    out << YAML::EndMap;
    std::fstream file("../config.yaml", std::ios::out);
    file << out.c_str();
    file.close();
} */