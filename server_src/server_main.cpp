#include "server/events/game_handler.h"

#include <unistd.h>
#include "common/network_acceptor.h"
#include "common/network_error.h"
/*
int main(int argc, char* args[]) {
    GameHandler gameHandler("../map.yaml", "../config.yaml");
    gameHandler.start();
    NetworkAcceptor networkAcceptor("8080");

    int total_connected = 0;
    while (total_connected < 2) {
        // Spawn clients
        try {
            NetworkConnection socket = std::move(networkAcceptor.acceptConnection());
            gameHandler.addNewPlayer(std::move(socket));
            total_connected++;
        } catch (const NetworkError& e) {
            continue;
        }
    }
    sleep(80);
    gameHandler.stop();
    gameHandler.join();
    return 0;
}
*/

int main() {
    Game game("../map.yaml", "../config.yaml");
    //game.movePlayer(1);
    //game.movePlayer(1);
    game.addBot();
    game.addBot();
    std::cout << "Gonna sleep main\n";
    sleep(2);
    std::cout << "Gonna release\n";
    game.releaseBots();
    std::cout << "Gonna sleep agai \n";
    sleep(7);

}

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