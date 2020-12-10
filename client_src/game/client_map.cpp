//
// Created by andy on 25/11/20.
//

#include <fstream>
#include <sstream>
#include <iterator>
#include <zconf.h>
#include <functional>
#include "client/client_map.h"
#include "client/client_positionable_handler.h"

ClientMap::ClientMap(SdlWindow& window, int width, int height) :
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
                //putPositionableAt(std::pair<int, int>(j, i), 1, "../client_src/resources/wall_3.gif");
                //printf("Se coloca una pared en (%d, %d)\n", j, i);
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

ClientPositionable& ClientMap::getPositionableAt(std::pair<int, int> coordinates) {
    return std::ref(info.at(coordinates));
}

bool ClientMap::wallAtGrid(int x_pos, int y_pos, int x_factor, int y_factor) {
    if (x_pos < 0 || y_pos < 0 || x_pos > real_width || y_pos > real_height)
        return false;
    std::pair<int, int> grid_coordinates =
            calculateGrid(x_pos, y_pos, x_factor, y_factor);
    bool wall_at_grid = wallAtGrid(grid_coordinates);
    if (wall_at_grid)
        //printf("Se devuelve la grilla (%d, %d)\n", grid_coordinates.first, grid_coordinates.second);
    return wall_at_grid;
}

void ClientMap::getObjectInfo(DrawingInfo& drawing_info, int x_pos, int y_pos,
                        int x_factor, int y_factor) {

    int x_coord = x_pos/grid_size*grid_size + x_factor*grid_size;
    int y_coord = y_pos/grid_size*grid_size + y_factor*grid_size;
    std::pair<int, int> grid_coordinates{x_coord, y_coord};
    if (wallAtGrid(x_pos, y_pos, x_factor, y_factor))
        loadWallInfo(drawing_info, grid_coordinates);
    else
        loadObjectInfo(drawing_info, x_pos, y_pos);
}

void ClientMap::loadWallInfo(DrawingInfo& drawing_info,
                       std::pair<int, int> grid_coordinates) {
    ClientPositionable positionable = info.at(grid_coordinates);
    drawing_info.object_type = positionable.getObjectType();
    drawing_info.is_sprite = false;
    drawing_info.texture_name = positionable.getTextureName();
}

void ClientMap::loadObjectInfo(DrawingInfo& drawing_info, int x_pos, int y_pos) {
    std::pair<int, int> coordinates{x_pos, y_pos};
    ClientPositionable positionable = info.at(coordinates);
    drawing_info.object_type = positionable.getObjectType();
    drawing_info.is_sprite = positionable.isSprite();
    drawing_info.texture_name = positionable.getTextureName();
    if (drawing_info.is_sprite)
        drawing_info.sprite_image_number = positionable.getCurrentImageNumber();
}

void ClientMap::putPlayerAt(std::string player_name, std::pair<int, int> coord) {
    positions.insert(std::pair<std::string, std::pair<int, int>>(player_name,
                                                                 coord));
}

void ClientMap::addWalls(std::vector<std::pair<int,int>> walls) {
    for (auto& wall : walls) {
        putPositionableAt(wall, 1, "../client_src/resources/wall_alt.jpg");
    }
}

void ClientMap::putPositionableAt(std::pair<int, int> coordinates,
                            int object_type,
                            std::string image_name) {
    ClientPositionable positionable = ClientPositionableHandler::createPositionableFromType
            (object_type, image_name);
    coordinates.first*= grid_size;
    coordinates.second*= grid_size;
    info.insert(std::pair<std::pair<int, int>,
            ClientPositionable>(coordinates,positionable));
}

