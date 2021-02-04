#include "server/game/map.h"
#include <iostream>
#include <string>
#include <cmath>

Map::Map() {}
Map::~Map() {}

Map::Map(int player_max_spawn_count) : max_players(player_max_spawn_count) {
    player_spawns.resize(player_max_spawn_count);
    player_positions.resize(player_max_spawn_count);
}

/* ADDERS */

void Map::putPositionableAt(Positionable item, Coordinate pos) {
    board[pos] = item;
}

void Map::putBlockingAtExact(Positionable blocking, Coordinate coordinates) {
    board[getNormalizedCoordinate(coordinates)] = blocking;
}

void Map::addPlayer(int i) {
    player_positions[i] = player_spawns[i];
}

/* VERIFIERS */

bool Map::isABlockingItemAt(const Coordinate& coordinates) {
    Coordinate normalize = getNormalizedCoordinate(coordinates);
    if(board.find(normalize) != board.end())
        return board.at(normalize).isBlocking();
    return false;
}

bool Map::isAPlayerAt(Coordinate &coordinate) {
    for (auto& coord : player_positions) {
        if (coord == coordinate) return true;
    }
    return false;
}

bool Map::isAPlayerInACell(Coordinate coordinate) {
    Coordinate normalize_coordinate = getNormalizedCoordinate(coordinate);
    for (auto& coord : player_positions) {
        if (getNormalizedCoordinate(coord) == coordinate) return true;
    }
    return false;
}

/* GETTERS */

Positionable Map::getBlockingItemAt(Coordinate coordinates) {
    return board.at(getNormalizedCoordinate(coordinates));
}

Coordinate Map::getNormalizedCoordinate(Coordinate coordinates) {
    int x_normalize = trunc(coordinates.x / grid_size) * grid_size;
    int y_normalize = trunc(coordinates.y / grid_size) * grid_size;
    Coordinate normalize(x_normalize, y_normalize);
    return normalize;
}

Positionable Map::getPositionableAt(Coordinate coordinates) {
    return board.at(coordinates);
}

int Map::getGlobalID() {
    int id = global_id;
    global_id++;
    return id;
}

Coordinate Map::getPlayerPosition(int id) {
    return player_positions[id];
}

int Map::getPlayerIDAtPosition(Coordinate coord) {
    for(int i = 0; i < player_positions.size(); i++) {
        if (player_positions[i] == coord) return i;
    }
    return -1;
}

std::map<Coordinate, Positionable>& Map::getBoard() { return board; }

/* ERASERS */

void Map::removeBlockingItemAt(Coordinate coordinates) {
    board.erase(getNormalizedCoordinate(coordinates));
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

void Map::removePlayer(int &i) {
    player_positions[i] = Coordinate(-1, -1);
}

/* OTHERS */

Coordinate Map::closePositionable(int units, Coordinate coord,
                                  std::set<Coordinate>& found_positionables) {
    for (int i = coord.x-units; i <= coord.x+units; i++) {
        for (int j = coord.y-units; j <= coord.y+units; j++) {
            Coordinate pos(i,j);
            if(board.find(pos) != board.end() && !board.at(pos).isBlocking()
                && found_positionables.find(pos) == found_positionables.end()) {
                found_positionables.insert(pos);
                return pos;
            }
        }
    }
    return Coordinate(0,0);
}

void Map::respawnPlayer(int id) {
    addPlayer(id);
}

void Map::setPlayerPosition(int i, Coordinate coord) {
    player_positions[i] = coord;
}

/* MAP INITIALIZER FUNCTIONS */

void Map::addBlockingItems(std::unordered_map<std::string,
        std::vector<Coordinate>>& blocking, PositionableHandler handler) {
    for (auto& type : blocking) {
        for (auto& coord : type.second) {
            Positionable positionable = handler.createBlockingItem(type.first, global_id);
            global_id++;
            putBlockingItemAt(coord, positionable);
        }
    }
}

void Map::addItems(std::unordered_map<std::string,
        std::vector<Coordinate>>& items, PositionableHandler handler) {
    for (auto& type : items) {
        for (auto& coord : type.second) {
            Positionable positionable = handler.createItem(type.first, global_id);
            global_id++;
            putPositionableAtCenter(coord, positionable);
        }
    }
}

void Map::addPlayerSpawns(std::unordered_map<std::string,
        std::vector<Coordinate>>& spawns) {
    for (auto& type : spawns) {
        for (auto& coord : type.second) {
            if (std::stoi(type.first) >= max_players) break;
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
}

void Map::putPositionableAtCenter(Coordinate coordinates, Positionable positionable) {
    coordinates.x = (coordinates.x * grid_size) + (int) grid_size/2;
    coordinates.y = (coordinates.y * grid_size) + (int) grid_size/2;
    board[coordinates] = positionable;
}

/* MAP PRINT */

void Map::show() {
    std::cout << "---------------------------------------------------------------" << "\n";
    std::cout << "Board\nCurrent Global ID: " << global_id << "\n";
    for (auto& elem : board) {
        std::cout << "Coord: (" << elem.first.x << ", " << elem.first.y
                  << ") - Elem: " << elem.second.getCategory() << " - "
                  << elem.second.getType() << " - " << elem.second.getId() << "\n";
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

