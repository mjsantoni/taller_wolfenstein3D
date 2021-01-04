//
// Created by andy on 25/11/20.
//

#ifndef TP_WOLFENSTEIN_MAP_H
#define TP_WOLFENSTEIN_MAP_H

#include <unordered_map>
#include <vector>
#include <map>
#include "positionable_mock.h"
#include "client_player.h"
#include "drawing_info.h"


class MapMock {
public:
    MapMock(int width, int height);
    //bool OnLoad(char* File);
    void putPlayerAt(std::string player_name, std::pair<int, int> coord);
    void putPositionableAt(std::pair<int, int> coordinates, int object_type,
                           std::string image_name);
    void putPositionableAt(int x_pos, int y_pos, int object_type,
                           std::string image_name);
    void update(ClientPlayer& player, int x, int y);
    void initialize();
    bool movementAllowed(int new_x, int new_y, bool x_incr, bool y_incr);
    int getGridSize();
    bool outOfVerticalBounds(int y_pos);
    bool outOfHorizontalBounds(int x_pos);
    bool wallAtGrid(std::pair<int, int> grid_coordinates);
    int getMaxDistance();
    std::pair<int, int> calculateGrid(int x_pos, int y_pos, int x_factor,
                                      int y_factor);
    std::pair<int, int> calculateGrid(int x_pos, int y_pos);
    PositionableMock& getPositionableAt(std::pair<int, int> coordinates);
    bool wallAtGrid(int x_pos, int y_pos, int x_factor, int y_factor);
    void getObjectInfo(DrawingInfo& drawing_info, int x_pos, int y_pos,
                       int x_factor, int y_factor);
    std::vector<PositionableMock> getAllObjects();
    int getWidth();
    int getHeight();
private:
    std::map<std::pair<int, int>, PositionableMock> info;
    std::map<PositionableMock, std::pair<int, int>> floating_info;
    std::vector<PositionableMock> objects;
    std::map<std::string, std::pair<int, int>> positions;
    int grid_size = 64;
    int width;
    int height;
    int real_width;
    int real_height;

    void erasePlayerFromOldPosition(std::pair<int, int> old_positions);
    void updatePositions(ClientPlayer& player, std::pair<int, int> old_position,
                         std::pair<int, int> new_position);
    void loadWallInfo(DrawingInfo& drawing_info,
                      std::pair<int, int> grid_coordinates);
    //void loadObjectInfo(DrawingInfo& drawing_info, int x_pos, int y_pos);
};


#endif //TP_WOLFENSTEIN_MAP_H

