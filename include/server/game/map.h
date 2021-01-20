#ifndef TP_WOLFENSTEIN_MAP_H
#define TP_WOLFENSTEIN_MAP_H

#include <unordered_map>
#include <vector>
#include <map>
#include <set>
#include "positionable.h"
#include "player.h"
#include "positionable_handler.h"
#include "coordinate.h"
#include "config_parser.h"

class Map {
private:
    int grid_size = 64;
    std::map<Coordinate, Positionable> board;
    std::vector<Coordinate> player_positions; //player[0] = pos_player_0
    std::vector<Coordinate> player_spawns; //player[0] = spawn_player_0
    int global_id = 0;

public:
    Map();

    Map(int player_max_spawn_count);

    void addBlockingItems(std::unordered_map<std::string,
                            std::vector<Coordinate>>& obstructives, PositionableHandler handler);
    void addItems(std::unordered_map<std::string,
                            std::vector<Coordinate>>& non_obstructives, PositionableHandler handler);
    void addPlayerSpawns(std::unordered_map<std::string,
                         std::vector<Coordinate>>& spawns);

    void putBlockingItemAt(Coordinate coordinate, Positionable positionable);
    void putPositionableAt(Coordinate coordinates, Positionable positionable);
    bool isABlockingItemAt(const Coordinate& coordinates);
    void show();

    Coordinate closePositionable(int units, Coordinate coord,
                                 std::set<Coordinate>& found_positionables);
    Positionable getPositionableAt(Coordinate coordinates);
    void erasePositionableAt(Coordinate coord);

    void addPlayer(int i);
    Coordinate getPlayerPosition(int id);
    void setPlayerPosition(int i, Coordinate pair);
    bool isAPlayerAt(Coordinate &coordinate);

    int getPlayerIDAtPosition(Coordinate coord);

    void respawnPlayer(int id);

    void removePlayer(int &i);

    void putPositionableAtExact(Positionable item, Coordinate pos);

    void addGlobalID();

    int getGlobalID() const;

    Positionable getBlockingItemAt(Coordinate coordinates);

    Coordinate getNormalizedCoordinate(Coordinate coordinates);

    void removeBlockingItemAt(Coordinate coordinates);

    void putBlockingAtExact(Positionable blocking, Coordinate coordinates);
};

#endif //TP_WOLFENSTEIN_MAP_H
