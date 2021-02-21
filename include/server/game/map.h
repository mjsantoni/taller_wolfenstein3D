#ifndef TP_WOLFENSTEIN_MAP_H
#define TP_WOLFENSTEIN_MAP_H

#include <unordered_map>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include "server/utils/map_generator.h"
#include "server/entities/positionable.h"
#include "server/game/player.h"
#include "server/game/positionable_handler.h"
#include "common/coordinate.h"

#define GRID_SIZE 64

class Map {
private:
    MapGenerator mapGenerator;
    PositionableHandler handler;
    int grid_size = GRID_SIZE;
    int global_id = 0;
    int max_players;
    std::unordered_map<Coordinate, Positionable, Coordinate::HashFunction> board;
    std::vector<Coordinate> player_positions; // player[0] = pos_player_0
    std::vector<Coordinate> player_spawns; // player[0] = spawn_player_0
    std::unordered_set<Coordinate, Coordinate::HashFunction> itemsPositions;
    std::unordered_set<Coordinate, Coordinate::HashFunction> doors_and_fake_pos;

public:
    Map(std::string map_path, int player_max_spawn_count);
    ~Map();

    /* ADDERS */

    void putPositionableAt(const Positionable &item, const Coordinate& pos);
    void addPlayer(int i);

    /* VERIFIERS */

    bool isABlockingItemAt(const Coordinate& coordinates);
    bool isAPlayerAt(Coordinate &coordinate);
    bool isAPlayerInACell(const Coordinate& coordinate);

    /* GETTERS */

    Positionable getBlockingItemAt(const Coordinate& coordinates);
    Coordinate getNormalizedCoordinate(const Coordinate& coordinates);
    Positionable getPositionableAt(const Coordinate& coordinates);
    int getGlobalID();
    Coordinate getPlayerPosition(int id);
    int getPlayerIDAtPosition(const Coordinate& coord);
    std::unordered_map<Coordinate, Positionable, Coordinate::HashFunction> getBoard();

    /* ERASERS */

    void removeBlockingItemAt(const Coordinate& coordinates);
    void erasePositionableAt(const Coordinate& coord);
    void removePlayer(int &i);

    /* OTHERS */

    Coordinate closePositionable(int units, const Coordinate& coord,
                                 std::set<Coordinate>& found_positionables);
    void respawnPlayer(int id);
    void setPlayerPosition(int i, const Coordinate& coordinate);

    /* MAP INITIALIZER FUNCTIONS */

    void addBlockingItems(std::unordered_map<std::string,
                            std::vector<Coordinate>>& obstructives, PositionableHandler handler);
    void addItems(std::unordered_map<std::string,
                            std::vector<Coordinate>>& non_obstructives, PositionableHandler handler);
    void addPlayerSpawns(std::unordered_map<std::string,
                         std::vector<Coordinate>>& spawns);
    void putBlockingItemAt(Coordinate coordinate, const Positionable& positionable);
    void putBlockingItemAtCenter(Coordinate coordinates, const Positionable &blocking);
    void putPositionableAtCenter(Coordinate coordinates, const Positionable& positionable);

    /* MAP PRINT */
    void show();

    Coordinate closeBlocking(int units, const Coordinate &coord, double self_angle);

    Coordinate getCenteredCoordinate(const Coordinate &coordinates);
};

#endif //TP_WOLFENSTEIN_MAP_H
