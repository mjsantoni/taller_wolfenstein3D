//
// Created by andy on 25/11/20.
//

#include <fstream>
#include <sstream>
#include <iterator>
#include <zconf.h>
#include <functional>
#include <client/drawable.h>
#include "client/client_map.h"

ClientMap::ClientMap(int width, int height, int grid_size) :
                                width(width), height(height) {
    real_width = width*grid_size;
    real_height = height*grid_size;
}

int ClientMap::getGridSize() {
    return grid_size;
}

void ClientMap::initialize() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (i == height-1 || i == 0 || j == width-1 || j == 0) {
            }
        }
    }
    //window.render();
}

bool ClientMap::outOfHorizontalBounds(int x_pos) {
    return x_pos < 0 || x_pos > real_width;
}

bool ClientMap::outOfVerticalBounds(int y_pos) {
    return y_pos < 0 || y_pos > real_height;
}

bool ClientMap::wallAtGrid(std::pair<int, int> grid_coordinates) {
    int x_pos = grid_coordinates.first*grid_size;
    int y_pos = grid_coordinates.second*grid_size;
    std::pair<int, int> coordinates(x_pos, y_pos);
    return info.find(coordinates) != info.end();
}

int ClientMap::getMaxDistance() {
    return (int) (sqrt(pow(real_width, 2)+pow(real_height, 2)));
}

std::pair<int, int> ClientMap::calculateGrid(int x_pos, int y_pos, int x_factor,
                                             int y_factor) {
    if (x_pos < 0 || y_pos < 0)
        return {-1, -1};
    int x_grid = x_pos/grid_size + x_factor;
    int y_grid = y_pos/grid_size + y_factor;
    return {x_grid, y_grid};
}

std::pair<int, int> ClientMap::calculateGrid(int x_pos, int y_pos) {
    int x_grid = x_pos/grid_size;
    int y_grid = y_pos/grid_size;
    return {x_grid, y_grid};
}

Drawable& ClientMap::getDrawableAt(std::pair<int, int> coordinates) {
    return std::ref(info.at(coordinates));
}

bool ClientMap::wallAtGrid(int x_pos, int y_pos, int x_factor, int y_factor) {
    if (x_pos < 0 || y_pos < 0 || x_pos > real_width || y_pos > real_height)
        return false;
    std::pair<int, int> grid_coordinates =
            calculateGrid(x_pos, y_pos, x_factor, y_factor);
    bool wall_at_grid = wallAtGrid(grid_coordinates);
    //if (wall_at_grid)
        //printf("Se devuelve la grilla (%d, %d)\n", grid_coordinates.first, grid_coordinates.second);
    return wall_at_grid;
}

bool ClientMap::wallAtPerimeter(int x_pos,
                                int y_pos,
                                int x_factor,
                                int y_factor) {
    if (x_pos < 0 || y_pos < 0 || x_pos > real_width || y_pos > real_height)
        return false;
    std::pair<int, int> grid_coordinates =
            calculateGrid(x_pos, y_pos, x_factor, y_factor);
    //printf("Se verifica la grilla (%d, %d)\n", grid_coordinates.first, grid_coordinates.second);
    bool is_at_horizontal_perimeter = grid_coordinates.first == 0 ||
            grid_coordinates.first == width-1;
    bool is_at_vertical_perimeter = grid_coordinates.second == 0 ||
                                    grid_coordinates.second == height-1;
    return is_at_horizontal_perimeter || is_at_vertical_perimeter;
}

void ClientMap::getObjectInfo(DrawingInfo& drawing_info, int x_pos, int y_pos,
                        int x_factor, int y_factor) {

    int x_coord = x_pos/grid_size*grid_size + x_factor*grid_size;
    int y_coord = y_pos/grid_size*grid_size + y_factor*grid_size;
    std::pair<int, int> grid_coordinates{x_coord, y_coord};
    if (wallAtGrid(x_pos, y_pos, x_factor, y_factor))
        loadWallInfo(drawing_info, grid_coordinates);
}

void ClientMap::loadWallInfo(DrawingInfo& drawing_info,
                       std::pair<int, int> grid_coordinates) {
    Drawable drawable = info.at(grid_coordinates);
    drawing_info.object_type = drawable.getObjectType();
}

void ClientMap::putPlayerAt(std::string player_name, std::pair<int, int> coord) {
    positions.insert(std::pair<std::string, std::pair<int, int>>(player_name,
                                                                 coord));
}

void ClientMap::addWalls(std::vector<std::pair<int,int>> walls) {
    for (auto& wall : walls) {
        //printf("se pone una pared en : (%d, %d)\n", wall.first, wall.second);
        putDrawableAt(wall, 0);
    }
    //putDrawableAt(std::pair<int, int>(4,2), 0);
    putDrawableAt(150,128,1);
    putDrawableAt(150,192,2);
    putDrawableAt(400,350,3);
    putDrawableAt(100,600,5);
    //putDrawableAt(750,100,6);
    putDrawableAt(700,250,8);
}

void ClientMap::putDrawableAt(std::pair<int, int> coordinates,
                            int object_type) {
    Drawable drawable(object_type);
    coordinates.first*= grid_size;
    coordinates.second*= grid_size;
    info.insert(std::pair<std::pair<int, int>,
            Drawable>(coordinates,drawable));
}

void ClientMap::putDrawableAt(int x_pos,
                                  int y_pos,
                                  int object_type) {
    Drawable drawable(object_type);
    drawable.setMapPosition(x_pos, y_pos);
    objects.push_back(drawable);
}

int ClientMap::getWidth() {
    return real_width;
}

int ClientMap::getHeight() {
    return real_height;
}

std::vector<Drawable> ClientMap::getAllObjects() {
    return objects;
}

