//
// Created by andy on 25/11/20.
//

#include <fstream>
#include <sstream>
#include <iterator>
#include <zconf.h>
#include <functional>
#include "client/game/map_mock.h"

MapMock::MapMock(int width, int height) : width(width), height(height) {
    real_width = width*grid_size;
    real_height = height*grid_size;
}

template <class Container>
void split(const std::string& str, Container& cont) {
    std::istringstream iss(str);
    std::copy(std::istream_iterator<std::string>(iss),
              std::istream_iterator<std::string>(),
              std::back_inserter(cont));
}

void MapMock::putPositionableAt(std::pair<int, int> coordinates,
                                int object_type,
                                std::string image_name) {
    PositionableMock positionable = ClientWall(image_name);
    coordinates.first*= grid_size;
    coordinates.second*= grid_size;
    info.insert(std::pair<std::pair<int, int>,
            PositionableMock>(coordinates, positionable));
}

void MapMock::putPositionableAt(int x_pos, int y_pos,
                                int object_type,
                                std::string image_name) {
    PositionableMock positionable = ClientWall(image_name);
    positionable.setPosition(x_pos, y_pos);
    std::pair<int, int> coordinates{x_pos, y_pos};
    objects.push_back(positionable);
}

void MapMock::putPlayerAt(std::string player_name, std::pair<int, int> coord) {
    positions.insert(std::pair<std::string, std::pair<int, int>>(player_name,
                                                                 coord));
}

void MapMock::update(ClientPlayer& player, int x, int y) {
    std::string player_name = player.getPlayerName();
    std::pair<int, int> old_position = positions.at(player_name);
    std::pair<int, int> new_position(x, y);
    if (new_position != old_position)
        erasePlayerFromOldPosition(old_position);
    updatePositions(player, old_position, new_position);
}

int MapMock::getGridSize() {
    return grid_size;
}

void MapMock::initialize() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (i == height-1 || i == 0 || j == width-1 || j == 0) {
                putPositionableAt(std::pair<int, int>(j, i), 1, "../Resources/wall_3.gif");
                //printf("Se coloca una pared en (%d, %d)\n", j, i);
            }
        }
    }

    putPositionableAt(250, 170, 3, "../Resources/bazooka_alt.png");
    putPositionableAt(std::pair<int, int>(4, 3), 1,"../Resources/wall_alt.jpg");
    putPositionableAt(std::pair<int, int>(1, 5), 1,"../Resources/wall_alt.jpg");
    putPositionableAt(std::pair<int, int>(2, 6), 1,"../Resources/wall_alt.jpg");
    //window.render();
}

void MapMock::erasePlayerFromOldPosition(std::pair<int, int> old_positions) {
    int pos_x = old_positions.first;
    int pos_y = old_positions.second;
    Area erase_area(pos_x, pos_y, grid_size, grid_size);
}

bool MapMock::movementAllowed(int new_x, int new_y, bool x_incr, bool y_incr) {
    if (new_x < 0 || new_y < 0 || new_x > real_width || new_y > real_height)
        return false;
    int x_grid = new_x/grid_size;
    int y_grid = new_y/grid_size;
    std::pair<int, int> coordinates{x_grid, y_grid};
    int x_coord = (new_x/grid_size)*grid_size + (int) x_incr*grid_size;
    int y_coord = (new_y/grid_size)*grid_size + (int) y_incr*grid_size;
    //std::pair<int, int> coordinates(x_coord, y_coord);
    bool is_allowed = !wallAtGrid(coordinates);
    if (! is_allowed)
        printf("El jugador no puede moverse a (%d,%d) porque hay una pared en (%d, %d)\n",
               new_x, new_y, x_coord, y_coord);
    return is_allowed;
}

void MapMock::updatePositions(ClientPlayer& player,
                              std::pair<int, int> old_position,
                              std::pair<int, int> new_position) {
    positions.erase(player.getPlayerName());
    positions.insert(std::pair<std::string,
            std::pair<int, int>>(player.getPlayerName(), new_position));
    if (info.find(old_position) != info.end())
        info.erase(old_position);
}

bool MapMock::outOfHorizontalBounds(int x_pos) {
    return x_pos < 0 || x_pos > real_width;
}

bool MapMock::outOfVerticalBounds(int y_pos) {
    return y_pos < 0 || y_pos > real_height;
}

bool MapMock::wallAtGrid(std::pair<int, int> grid_coordinates) {
    int x_pos = grid_coordinates.first*grid_size;
    int y_pos = grid_coordinates.second*grid_size;
    std::pair<int, int> coordinates(x_pos, y_pos);
    return info.find(coordinates) != info.end();
}

int MapMock::getMaxDistance() {
    return (int) (sqrt(pow(real_width, 2)+pow(real_height, 2)));
}

std::pair<int, int> MapMock::calculateGrid(int x_pos, int y_pos, int x_factor,
                                           int y_factor) {
    if (x_pos < 0 || y_pos < 0)
        return {-1, -1};
    int x_grid = x_pos/grid_size + x_factor;
    int y_grid = y_pos/grid_size + y_factor;
    return {x_grid, y_grid};
}

std::pair<int, int> MapMock::calculateGrid(int x_pos, int y_pos) {
    int x_grid = x_pos/grid_size;
    int y_grid = y_pos/grid_size;
    return {x_grid, y_grid};
}

PositionableMock& MapMock::getPositionableAt(std::pair<int, int> coordinates) {
    return std::ref(info.at(coordinates));
}

bool MapMock::wallAtGrid(int x_pos, int y_pos, int x_factor, int y_factor) {
    if (x_pos < 0 || y_pos < 0 || x_pos > real_width || y_pos > real_height)
        return false;
    std::pair<int, int> grid_coordinates =
            calculateGrid(x_pos, y_pos, x_factor, y_factor);
    bool wall_at_grid = wallAtGrid(grid_coordinates);
    //if (wall_at_grid)
        //printf("Se devuelve la grilla (%d, %d)\n", grid_coordinates.first, grid_coordinates.second);
    return wall_at_grid;
}

void MapMock::getObjectInfo(ObjectInfo& object_info, int x_pos, int y_pos,
                            int x_factor, int y_factor) {

    int x_coord = x_pos/grid_size*grid_size + x_factor*grid_size;
    int y_coord = y_pos/grid_size*grid_size + y_factor*grid_size;
    std::pair<int, int> grid_coordinates{x_coord, y_coord};
    loadWallInfo(object_info, grid_coordinates);
}

void MapMock::loadWallInfo(ObjectInfo& object_info,
                           std::pair<int, int> grid_coordinates) {
    PositionableMock positionable = info.at(grid_coordinates);
    object_info.setObjectType(positionable.getObjectType());
    object_info.setMapStartingPos(positionable.getPosition());
}

std::vector<PositionableMock> MapMock::getAllObjects() {
    return objects;
}
/*
void MapMock::loadObjectInfo(MapInfo& drawing_info, int x_pos, int y_pos) {
    std::pair<int, int> coordinates{x_pos, y_pos};
    Positionable positionable = floating_info.at(coordinates);
    drawing_info.object_type = positionable.getObjectType();
    drawing_info.is_sprite = positionable.isSprite();
    drawing_info.texture_name = positionable.getTextureName();
    if (drawing_info.is_sprite)
        drawing_info.sprite_image_number = positionable.getCurrentImageNumber();
}
*/

int MapMock::getWidth() {
    return real_width;
}

int MapMock::getHeight() {
    return real_height;
}

