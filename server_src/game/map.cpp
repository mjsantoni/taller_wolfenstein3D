#include "server/game/map.h"
#include <iostream>
#include <string>
#include <cmath>

Map::~Map() {}

Map::Map(std::string map_path, int player_max_spawn_count)
    : mapGenerator(map_path), max_players(player_max_spawn_count) {
  player_spawns.resize(player_max_spawn_count);
  player_positions.resize(player_max_spawn_count);

  std::unordered_map<std::string, std::vector<Coordinate>> positionables;

  positionables = mapGenerator.getWalls();
  addBlockingItems(positionables, handler);

  positionables = mapGenerator.getItems();
  addItems(positionables, handler);

  positionables = mapGenerator.getPlayerSpawns();
  addPlayerSpawns(positionables);
}

/* ADDERS */

void Map::putPositionableAt(const Positionable& item, const Coordinate& pos) {
  board[pos] = item;
  if (!item.isBlocking()) itemsPositions.insert(pos);
  if (item.getCategory() == "door" || item.getType() == "fake_wall") {
    doors_and_fake_pos.insert(pos);
  }
}

void Map::addPlayer(int i) {
  player_positions[i] = player_spawns[i];
}

/* VERIFIERS */

bool Map::isABlockingItemAt(const Coordinate& coordinates) {
  Coordinate normalize = getNormalizedCoordinate(coordinates);
  Coordinate centered = getCenteredCoordinate(coordinates);
  if (board.find(centered) != board.end()) return board.at(centered).isBlocking();
  if (board.find(normalize) != board.end()) return board.at(normalize).isBlocking();
  return false;
}

bool Map::isAPlayerAt(Coordinate& coordinate) {
  for (auto& coord : player_positions) {
    if (coord == coordinate) return true;
  }
  return false;
}

bool Map::isAPlayerInACell(const Coordinate& coordinate) {
  Coordinate normalize_coordinate = getNormalizedCoordinate(coordinate);
  for (auto& coord : player_positions) {
    if (getNormalizedCoordinate(coord) == coordinate) return true;
  }
  return false;
}

/* GETTERS */

Positionable Map::getBlockingItemAt(const Coordinate& coordinates) {
  return board.at(getNormalizedCoordinate(coordinates));
}

Coordinate Map::getNormalizedCoordinate(const Coordinate& coordinates) {
  int x_normalize = trunc(coordinates.x / grid_size) * grid_size;
  int y_normalize = trunc(coordinates.y / grid_size) * grid_size;
  Coordinate normalize(x_normalize, y_normalize);
  return normalize;
}

Coordinate Map::getCenteredCoordinate(const Coordinate& coordinates) {
  int x_normalize = trunc(coordinates.x / grid_size);
  int y_normalize = trunc(coordinates.y / grid_size);
  Coordinate normalize(x_normalize, y_normalize);
  normalize.x = (normalize.x * grid_size) + (int) grid_size / 2;
  normalize.y = (normalize.y * grid_size) + (int) grid_size / 2;
  return normalize;
}

Positionable Map::getPositionableAt(const Coordinate& coordinates) {
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

int Map::getPlayerIDAtPosition(const Coordinate& coord) {
  for (int i = 0; i < player_positions.size(); i++) {
    if (player_positions[i] == coord) return i;
  }
  return -1;
}

std::unordered_map<Coordinate, Positionable, Coordinate::HashFunction> Map::getBoard() { return board; }

/* ERASERS */

void Map::removeBlockingItemAt(const Coordinate& coordinates) {
  board.erase(getNormalizedCoordinate(coordinates));
  doors_and_fake_pos.erase(getNormalizedCoordinate(coordinates));
}

void Map::erasePositionableAt(const Coordinate& coord) {
  if (board.find(coord) != board.end()) {
    board.erase(coord);
    itemsPositions.erase(coord);
  } else return;
}

void Map::removePlayer(int& i) { player_positions[i] = Coordinate(-1, -1); }

/* OTHERS */

Coordinate Map::closePositionable(int units, const Coordinate& coord,
                                  std::set<Coordinate>& found_positionables) {
  for (auto& item_coord : itemsPositions) {
    if (item_coord.distanceTo(coord) <= units &&
        found_positionables.find(item_coord) == found_positionables.end()) {
      found_positionables.insert(item_coord);
      return item_coord;
    }
  }
  return Coordinate(0, 0);
}

bool insideAngle(double facing, double target) {
  double dot = cos(facing) * cos(target) + sin(facing) * sin(target);
  double interval = acos(dot);
  return interval <= M_PI / 6;
}

double angleBetween(const Coordinate& self_pos, const Coordinate& other_pos) {
  int new_x = (-self_pos.x) - (-other_pos.x);
  int new_y = (self_pos.y) - (other_pos.y);
  return (atan2(new_y, new_x));
}

Coordinate Map::closeBlocking(int units, const Coordinate& coord, double self_angle) {
  for (auto& blocking_coord : doors_and_fake_pos) {
    Coordinate blocking_centered(blocking_coord.x + 32, blocking_coord.y + 32);
    bool in_sight = insideAngle(self_angle, angleBetween(coord, blocking_centered));
    if (blocking_centered.distanceTo(coord) <= units && in_sight)
      return blocking_coord;
  }
  return Coordinate(-1, -1);
}

void Map::respawnPlayer(int id) { addPlayer(id); }

void Map::setPlayerPosition(int i, const Coordinate& coord) { player_positions[i] = coord; }

/* MAP INITIALIZER FUNCTIONS */

void Map::addBlockingItems(std::unordered_map<std::string,
                                              std::vector<Coordinate>>& blocking, PositionableHandler handler) {
  for (auto& type : blocking) {
    for (auto& coord : type.second) {
      Positionable positionable = handler.createBlockingItem(type.first, global_id);
      global_id++;
      if (positionable.getCategory() == "misc") putBlockingItemAtCenter(coord, positionable);
      else putBlockingItemAt(coord, positionable);
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
      coord.x = (coord.x * grid_size) + (int) grid_size / 2;
      coord.y = (coord.y * grid_size) + (int) grid_size / 2;
      player_spawns[std::stoi(type.first)] = coord;
    }
  }
}

void Map::putBlockingItemAt(Coordinate coordinates,
                            const Positionable& positionable) {
  coordinates.x *= grid_size;
  coordinates.y *= grid_size;
  board[coordinates] = positionable;
  if (positionable.getCategory() == "door" || positionable.getType() == "fake_wall") {
    doors_and_fake_pos.insert(coordinates);
  }
}

void Map::putBlockingItemAtCenter(Coordinate coordinates, const Positionable& blocking) {
  coordinates.x = (coordinates.x * grid_size) + (int) grid_size / 2;
  coordinates.y = (coordinates.y * grid_size) + (int) grid_size / 2;
  board[coordinates] = blocking;
}

void Map::putPositionableAtCenter(Coordinate coordinates, const Positionable& positionable) {
  coordinates.x = (coordinates.x * grid_size) + (int) grid_size / 2;
  coordinates.y = (coordinates.y * grid_size) + (int) grid_size / 2;
  board[coordinates] = positionable;
  itemsPositions.insert(coordinates);
}
