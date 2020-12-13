#include <iterator>
#include "server/map.h"
#include "server/positionable.h"
#include <iostream>
#include <string>
#include <cmath>
#include <functional>

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

bool Map::isABlockingItem(std::pair<int, int> coordinates) {
    int x_normalize = trunc(coordinates.first / grid_size) * grid_size;
    int y_normalize = trunc(coordinates.second / grid_size) * grid_size;
    std::pair<int, int> normalize(x_normalize, y_normalize);
    if(board.find(normalize) != board.end())
        return !board.at(normalize).isBlocking();
    return true;
}

std::pair<int, int> Map::closePositionable(int units, std::pair<int,int> coord) {
    for (int i = coord.first-units; i <= coord.first+units; i++) {
        for (int j = coord.second-units; j <= coord.second+units; j++) {
            std::pair<int, int> pos(i,j);
            if(board.find(pos) != board.end() && !board.at(pos).isBlocking()) {
                return pos;
            }
        }
    }
    return std::make_pair(0,0);
}

Positionable Map::getPositionableAt(std::pair<int, int> coordinates) {
    return board.at(coordinates);
}

void Map::erasePositionableAt(std::pair<int,int> coord) {
    if (board.find(coord) != board.end()) {
        //no deberia dar error, esto deberia borrar de una
        //gasta recursos chequear esto
        board.erase(coord);
        std::cout << "Borro en: (" << coord.first << ", " << coord.second << ")\n";
    } else {
        std::cout << "No habia nada, error en la posicion recibida\n";
    }
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
