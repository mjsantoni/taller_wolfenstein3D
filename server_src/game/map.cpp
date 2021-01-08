#include <iterator>
#include "server/game/map.h"
#include "server/game/positionable.h"
#include <iostream>
#include <string>
#include <cmath>
#include <functional>

Map::Map() {}

Map::Map(int player_max_spawn_count)   {
    player_spawns.resize(player_max_spawn_count);
    player_positions.resize(player_max_spawn_count);
}

void Map::addBlockingItems(std::unordered_map<std::string,
                            std::vector<Coordinate>>& blocking) {
    for (auto& type : blocking) {
        for (auto& coord : type.second) {
            Positionable positionable = handler.createBlockingItem(type.first);
            putBlockingItemAt(coord, positionable);
        }
    }
}

void Map::addItems(std::unordered_map<std::string,
                    std::vector<Coordinate>>& items) {
    for (auto& type : items) {
        for (auto& coord : type.second) {
            Positionable positionable = handler.createItem(type.first);
            putPositionableAt(coord, positionable);
        }
    }
}

void Map::addPlayerSpawns(std::unordered_map<std::string,
                            std::vector<Coordinate>>& spawns) {
    for (auto& type : spawns) {
        for (auto& coord : type.second) {
            coord.x = (coord.x * grid_size) + (int) grid_size/2;
            coord.y = (coord.y * grid_size) + (int) grid_size/2;
            player_spawns[std::stoi(type.first)] = coord;
        }
    }
}

void Map::putBlockingItemAt(Coordinate coordinates,
                            Positionable positionable) {
    coordinates.x *= grid_size;
    coordinates.y *= grid_size;
    board[coordinates] = positionable;
    //board.insert(std::pair<Coordinate,
    //        Positionable>(coordinates,positionable));
}

void Map::putPositionableAt(Coordinate coordinates, Positionable positionable) {
    coordinates.x = (coordinates.x * grid_size) + (int) grid_size/2;
    coordinates.y = (coordinates.y * grid_size) + (int) grid_size/2;
    board[coordinates] = positionable;
    //board.insert(std::pair<Coordinate,
    //        Positionable>(coordinates,positionable));
}

bool Map::isABlockingItem(Coordinate coordinates) {
    int x_normalize = trunc(coordinates.x / grid_size) * grid_size;
    int y_normalize = trunc(coordinates.y / grid_size) * grid_size;
    Coordinate normalize(x_normalize, y_normalize);
    if(board.find(normalize) != board.end())
        return !board.at(normalize).isBlocking();
    return true;
}

Coordinate Map::closePositionable(int units, Coordinate coord) {
    for (int i = coord.x-units; i <= coord.x+units; i++) {
        for (int j = coord.y-units; j <= coord.y+units; j++) {
            Coordinate pos(i,j);
            if(board.find(pos) != board.end() && !board.at(pos).isBlocking()) {
                return pos;
            }
        }
    }
    return Coordinate(0,0);
}

Positionable Map::getPositionableAt(Coordinate coordinates) {
    return board.at(coordinates);
}

void Map::erasePositionableAt(Coordinate coord) {
    if (board.find(coord) != board.end()) {
        //no deberia dar error, esto deberia borrar de una
        //gasta recursos chequear esto
        board.erase(coord);
        std::cout << "Borro en: (" << coord.x << ", " << coord.y << ")\n";
    } else {
        std::cout << "No habia nada, error en la posicion recibida\n";
    }
}


void Map::show() {
    std::cout << "---------------------------------------------------------------" << "\n";
    std::cout << "Board\n";
    for (auto& elem : board) {
        std::cout << "Coord: (" << elem.first.x << ", " << elem.first.y
                  << ") - Elem: " << elem.second.getCategory() << " - "
                                  << elem.second.getType() << "\n";
    }
    std::cout << "Player Spawns\n";
    int i = 0;
    for (auto& spawn : player_spawns) {
        std::cout << "Player " << i << " -> (" << spawn.x << ", " << spawn.y << ")\n";
        i++;
    }
    std::cout << "Player Positions\n";
    i = 0;
    for (auto& spawn : player_positions) {
        std::cout << "Player " << i << " -> (" << spawn.x << ", " << spawn.y << ")\n";
        i++;
    }
    std::cout << "---------------------------------------------------------------\n";
}

void Map::addPlayer(int i) {
    player_positions[i] = player_spawns[i];
}

Coordinate Map::getPlayerPosition(int id) {
    return player_positions[id];
}

void Map::setPlayerPosition(int i, Coordinate coord) {
    player_positions[i] = coord;
}

int Map::getPlayerIDAtPosition(Coordinate coord) {
    for(int i = 0; i < player_positions.size(); i++) {
        if (player_positions[i] == coord) return i;
    }
    return -1;
}

bool Map::isAPlayerAt(Coordinate &coordinate) {
    for (auto& coord : player_positions) {
        if (coord == coordinate) return true;
    }
    return false;
}
