//
// Created by andy on 25/11/20.
//

#ifndef TP_WOLFENSTEIN_MAP_H
#define TP_WOLFENSTEIN_MAP_H

#include <unordered_map>
#include <vector>
#include <map>
#include "positionable.h"
#include "player.h"
#include "positionable_handler.h"
#include "coordinate.h"
class Map {
private:
    int grid_size = 64;
    std::map<Coordinate, Positionable> board;
    std::vector<Coordinate> player_positions; //player[0] = pos_player_0
    std::vector<Coordinate> player_spawns; //player[0] = spawn_player_0
    PositionableHandler handler;
    //TDA que guarde modif y eventos

public:
    Map();
    Map(int player_max_spawn_count);
    void addBlockingItems(std::unordered_map<std::string,
                            std::vector<Coordinate>>& obstructives);
    void addItems(std::unordered_map<std::string,
                            std::vector<Coordinate>>& non_obstructives);
    void addPlayerSpawns(std::unordered_map<std::string,
                            std::vector<Coordinate>>& player_spawns);


    void putBlockingItemAt(Coordinate coordinate, Positionable positionable);
    void putPositionableAt(Coordinate coordinates, Positionable positionable);
    bool isABlockingItem(Coordinate coordinates);
    void show();

    Coordinate closePositionable(int units, Coordinate coord);
    Positionable getPositionableAt(Coordinate coordinates);

    void erasePositionableAt(Coordinate coord);

    void addPlayer(int i);

    Coordinate getPlayerPosition(int id);

    void setPlayerPosition(int i, Coordinate pair);
};




    /*
    Map(int width, int height);
    //bool OnLoad(char* File);
    void putPlayerAt(std::string player_name, Coordinate coord);
    void putPositionableAt(Coordinate coordinates, int object_type,
                           std::string image_name);
    void update(Player& player, int x, int y);
    void initialize();
    bool movementAllowed(int new_x, int new_y, bool x_incr, bool y_incr);
    int getGridSize();

    bool wallAtGrid(Coordinate grid_coordinates);
    int getMaxDistance();
    Coordinate calculateGrid(int x_pos, int y_pos, int x_factor,
                                      int y_factor);
    Coordinate calculateGrid(int x_pos, int y_pos);
    Positionable& getPositionableAt(Coordinate coordinates);
    bool wallAtGrid(int x_pos, int y_pos, int x_factor, int y_factor);
    void getObjectInfo(DrawingInfo& drawing_info, int x_pos, int y_pos,
                       int x_factor, int y_factor);
private:


    int grid_size = 64;
    int width;
    int height;
    int real_width;
    int real_height;

    void erasePlayerFromOldPosition(Coordinate old_positions);
    void updatePositions(Player& player, Coordinate old_position,
                         Coordinate new_position);
    void loadWallInfo(DrawingInfo& drawing_info,
                      Coordinate grid_coordinates);
    void loadObjectInfo(DrawingInfo& drawing_info, int x_pos, int y_pos);
     */



#endif //TP_WOLFENSTEIN_MAP_H
