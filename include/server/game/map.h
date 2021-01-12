#ifndef TP_WOLFENSTEIN_MAP_H
#define TP_WOLFENSTEIN_MAP_H

#include <unordered_map>
#include <vector>
#include <map>
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
    PositionableHandler handler;
    int global_id = 0;
    //TDA que guarde modif y eventos

public:
    Map();
    Map(int player_max_spawn_count, std::string _config_path);

    void addBlockingItems(std::unordered_map<std::string,
                            std::vector<Coordinate>>& obstructives);
    void addItems(std::unordered_map<std::string,
                            std::vector<Coordinate>>& non_obstructives);
    void addPlayerSpawns(std::unordered_map<std::string,
                            std::vector<Coordinate>>& player_spawns);

    void putBlockingItemAt(Coordinate coordinate, Positionable positionable);
    void putPositionableAt(Coordinate coordinates, Positionable positionable);
    bool isABlockingItemAt(Coordinate coordinates);
    void show();

    Coordinate closePositionable(int units, Coordinate coord);
    Positionable getPositionableAt(Coordinate coordinates);
    void erasePositionableAt(Coordinate coord);

    void addPlayer(int i);
    Coordinate getPlayerPosition(int id);
    void setPlayerPosition(int i, Coordinate pair);
    bool isAPlayerAt(Coordinate &coordinate);

    int getPlayerIDAtPosition(Coordinate coord);
};

#endif //TP_WOLFENSTEIN_MAP_H
