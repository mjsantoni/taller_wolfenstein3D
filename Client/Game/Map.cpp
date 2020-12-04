//
// Created by andy on 25/11/20.
//

#include <fstream>
#include <sstream>
#include <iterator>
#include <zconf.h>
#include <functional>
#include "Map.h"
#include "Wall.h"

Map::Map(SdlWindow& window, int width, int height) :
                                window(window), width(width), height(height) {
    this->window.fill();
    this->window.render();
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

void Map::putPositionableAt(Player& player, std::pair<int, int> coordinates) {
    std::string player_name = player.getPlayerName();
    Area src_area;
    positions.insert(std::pair<std::string,
                     std::pair<int, int>>(player_name, coordinates));
    SDL_Texture* player_image = player.getImage(window.getRenderer(), src_area);
    Area destArea(coordinates.first, coordinates.second, grid_size, grid_size);
    //window.putTextureAt(player_image, src_area, destArea);
}

void Map::putPositionableAt(std::pair<int, int> coordinates) {
    Wall wall;
    Area src_area;
    coordinates.first*= grid_size;
    coordinates.second*= grid_size;
    //window.putTextureAt(wall_image, src_area, dest_area);
    info.insert(std::pair<std::pair<int, int>, Positionable>(coordinates,wall));
}

void Map::update(Player& player, int x, int y) {
    std::string player_name = player.getPlayerName();
    std::pair<int, int> old_position = positions.at(player_name);
    std::pair<int, int> new_position(x, y);
    Area srcArea;
    SDL_Texture* player_image = player.getImage(window.getRenderer(), srcArea);
    Area destArea(x, y, grid_size, grid_size);
    if (new_position != old_position)
        erasePlayerFromOldPosition(old_position);
    //window.putTextureAt(player_image, srcArea, destArea);
    //window.render();
    updatePositions(player, old_position, new_position);
}

void Map::reset() {
    window.fill();
}

int Map::getGridSize() {
    return grid_size;
}

void Map::initialize() {
    window.fill();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (i == height-1 || i == 0 || j == width-1 || j == 0) {
                putPositionableAt(std::pair<int, int>(j, i));
                //printf("Se coloca una pared en (%d, %d)\n", j, i);
            }
        }
    }

    putPositionableAt(std::pair<int, int>(4, 3));
    putPositionableAt(std::pair<int, int>(1, 5));
    putPositionableAt(std::pair<int, int>(2, 6));
    //window.render();
}

void Map::erasePlayerFromOldPosition(std::pair<int, int> old_positions) {
    int pos_x = old_positions.first;
    int pos_y = old_positions.second;
    Area erase_area(pos_x, pos_y, grid_size, grid_size);
    window.fillSquare(erase_area);
}

bool Map::movementAllowed(int new_x, int new_y, bool x_incr, bool y_incr) {
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

void Map::updatePositions(Player& player,
                          std::pair<int, int> old_position,
                          std::pair<int, int> new_position) {
    positions.erase(player.getName());
    positions.insert(std::pair<std::string,
            std::pair<int, int>>(player.getName(), new_position));
    if (info.find(old_position) != info.end())
        info.erase(old_position);
    info.insert(std::pair<std::pair<int, int>, Positionable>(new_position,
                                                             player));
}

bool Map::outOfHorizontalBounds(int x_pos) {
    return x_pos < 0 || x_pos > real_width;
}

bool Map::outOfVerticalBounds(int y_pos) {
    return y_pos < 0 || y_pos > real_height;
}

bool Map::wallAtGrid(std::pair<int, int> grid_coordinates) {
    int x_pos = grid_coordinates.first*grid_size;
    int y_pos = grid_coordinates.second*grid_size;
    std::pair<int, int> coordinates(x_pos, y_pos);
    return info.find(coordinates) != info.end();
}

int Map::getMaxDistance() {
    return (int) (sqrt(pow(real_width, 2)+pow(real_height, 2)));
}

std::pair<int, int> Map::calculateGrid(int x_pos, int y_pos, int x_factor,
                                             int y_factor) {
    if (x_pos < 0 || y_pos < 0)
        return {-1, -1};
    int x_grid = x_pos/grid_size + x_factor;
    int y_grid = y_pos/grid_size + y_factor;
    return {x_grid, y_grid};
}

std::pair<int, int> Map::calculateGrid(int x_pos, int y_pos) {
    int x_grid = x_pos/grid_size;
    int y_grid = y_pos/grid_size;
    return {x_grid, y_grid};
}

Positionable& Map::getPositionableAt(std::pair<int, int> coordinates) {
    return std::ref(info.at(coordinates));
}

bool Map::wallAtGrid(int x_pos, int y_pos, int x_factor, int y_factor,
                     int player_x, int player_y) {
    if (x_pos < 0 || y_pos < 0 || x_pos > real_width || y_pos > real_height)
        return false;
    std::pair<int, int> grid_coordinates =
            calculateGrid(x_pos, y_pos, x_factor, y_factor);
    bool wall_at_grid = wallAtGrid(grid_coordinates);
    if (wall_at_grid)
        //printf("Se devuelve la grilla (%d, %d)\n", grid_coordinates.first, grid_coordinates.second);
    //if (!wall_at_grid)
        //wall_at_grid = checkBorderCase(player_x, player_y, grid_coordinates);
    return wall_at_grid;
}