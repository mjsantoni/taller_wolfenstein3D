//
// Created by andy on 25/11/20.
//

#ifndef TP_WOLFENSTEIN_CLIENT_MAP_H
#define TP_WOLFENSTEIN_CLIENT_MAP_H

#include <unordered_map>
#include <vector>
#include <map>
#include "positionable_mock.h"
#include "sdl_window.h"
#include "sdl_texture.h"
#include "client_player.h"

class ClientMap {
public:
    ClientMap() = default;
    ClientMap(int width, int height, int grid_size);
    //bool OnLoad(char* File);
    void initialize();
    int getGridSize();
    bool outOfVerticalBounds(int y_pos);
    bool outOfHorizontalBounds(int x_pos);
    bool wallAtGrid(std::pair<int, int> grid_coordinates);
    int getMaxDistance();
    int getWidth();
    int getHeight();
    std::pair<int, int> calculateGrid(int x_pos, int y_pos, int x_factor,
                                      int y_factor);
    std::pair<int, int> calculateGrid(int x_pos, int y_pos);
    Drawable& getDrawableAt(std::pair<int, int> coordinates);
    bool wallAtGrid(int x_pos, int y_pos, int x_factor, int y_factor);
    bool wallAtPerimeter(int x_pos, int y_pos, int x_factor, int y_factor);
    void getObjectInfo(DrawingInfo& drawing_info, int x_pos, int y_pos,
                       int x_factor, int y_factor);
    void putPlayerAt(std::string player_name, std::pair<int, int> coord);
    void addWalls(std::vector<std::pair<int,int>> walls);
    void putDrawableAt(std::pair<int, int> coordinates, int object_type);
    void putDrawableAt(int x_pos, int y_pos, int object_type);
    std::vector<Drawable> getAllObjects();


private:
    std::map<std::pair<int, int>, Drawable> info;
    int grid_size = 64;
    int width;
    int height;
    int real_width;
    int real_height;
    std::vector<Drawable> objects;
    std::map<std::string, std::pair<int, int>> positions;

    void loadWallInfo(DrawingInfo& drawing_info,
                      std::pair<int, int> grid_coordinates);
};


#endif //TP_WOLFENSTEIN_CLIENT_MAP_H
