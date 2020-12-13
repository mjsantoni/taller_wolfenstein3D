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

class Map {
private:
    int grid_size = 64;
    std::map<std::pair<int, int>, Positionable> board;
    std::vector<std::pair<int, int>> player_positions; //player[0] = pos_player_0
    std::vector<std::pair<int, int>> player_spawns; //player[0] = spawn_player_0
    PositionableHandler handler;
    //TDA que guarde modif y eventos

public:
    Map(int player_max_spawn_count);
    void addBlockingItems(std::unordered_map<std::string,
                            std::vector<std::pair<int, int>>>& obstructives);
    void addItems(std::unordered_map<std::string,
                            std::vector<std::pair<int, int>>>& non_obstructives);
    void addPlayerSpawns(std::unordered_map<std::string,
                            std::vector<std::pair<int, int>>>& player_spawns);

    void putPositionableAt(std::pair<int, int> coordinates, Positionable positionable);
    bool isABlockingItem(std::pair<int, int> coordinates);
    //bool isAValidXCoord(std::pair<int, int> coordinates);
    //bool isAValidYCoord(std::pair<int, int> coordinates);
    void show();

    std::pair<int, int> closePositionable(int units, std::pair<int, int> coord);
    Positionable getPositionableAt(std::pair<int, int> coordinates);



};




    /*
    Map(int width, int height);
    //bool OnLoad(char* File);
    void putPlayerAt(std::string player_name, std::pair<int, int> coord);
    void putPositionableAt(std::pair<int, int> coordinates, int object_type,
                           std::string image_name);
    void update(Player& player, int x, int y);
    void initialize();
    bool movementAllowed(int new_x, int new_y, bool x_incr, bool y_incr);
    int getGridSize();

    bool wallAtGrid(std::pair<int, int> grid_coordinates);
    int getMaxDistance();
    std::pair<int, int> calculateGrid(int x_pos, int y_pos, int x_factor,
                                      int y_factor);
    std::pair<int, int> calculateGrid(int x_pos, int y_pos);
    Positionable& getPositionableAt(std::pair<int, int> coordinates);
    bool wallAtGrid(int x_pos, int y_pos, int x_factor, int y_factor);
    void getObjectInfo(DrawingInfo& drawing_info, int x_pos, int y_pos,
                       int x_factor, int y_factor);
private:


    int grid_size = 64;
    int width;
    int height;
    int real_width;
    int real_height;

    void erasePlayerFromOldPosition(std::pair<int, int> old_positions);
    void updatePositions(Player& player, std::pair<int, int> old_position,
                         std::pair<int, int> new_position);
    void loadWallInfo(DrawingInfo& drawing_info,
                      std::pair<int, int> grid_coordinates);
    void loadObjectInfo(DrawingInfo& drawing_info, int x_pos, int y_pos);
     */



#endif //TP_WOLFENSTEIN_MAP_H
