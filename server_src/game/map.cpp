#include <iterator>
#include "server/map.h"
#include "server/positionable.h"
#include <iostream>
#include <string>

Map::Map(int player_max_spawn_count)   {
    player_spawns.resize(player_max_spawn_count);
}

void Map::addBlockingItems(std::unordered_map<std::string,
                            std::vector<std::pair<int, int>>>& blocking) {
    for (auto& type : blocking) {
        for (auto& coord : type.second) {
            Positionable positionable = handler.createBlockingItem(type.first);
            putPositionableAt(coord, positionable);
        }
    }
}

void Map::addItems(std::unordered_map<std::string,
                    std::vector<std::pair<int, int>>>& items) {
    for (auto& type : items) {
        for (auto& coord : type.second) {
            Positionable positionable = handler.createItem(type.first);
            putPositionableAt(coord, positionable);
        }
    }
}

void Map::addPlayerSpawns(std::unordered_map<std::string,
                            std::vector<std::pair<int, int>>>& spawns) {
    for (auto& type : spawns) {
        for (auto& coord : type.second) {
            coord.first *= grid_size;
            coord.second *= grid_size;
            player_spawns[std::stoi(type.first)] = coord;
        }
    }
}

void Map::putPositionableAt(std::pair<int, int> coordinates,
                            Positionable positionable) {
    coordinates.first *= grid_size;
    coordinates.second *= grid_size;
    board.insert(std::pair<std::pair<int, int>,
            Positionable>(coordinates,positionable));
}

void Map::show() {
    std::cout << "Board\n";
    for (auto& elem : board) {
        std::cout << "Coord: (" << elem.first.first << ", " << elem.first.second
        << ") - Elem: " << elem.second.getType() << "\n";
    }
    std::cout << "Player Spawns\n";
    int i = 0;
    for (auto& spawn : player_spawns) {
        std::cout << "Player " << i << " -> (" << spawn.first << ", " << spawn.second << ")\n";
        i++;
    }
}

