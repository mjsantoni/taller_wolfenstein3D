//
// Created by andy on 25/11/20.
//

#include <fstream>
#include <sstream>
#include <iterator>
#include <zconf.h>
#include <functional>
#include "client/game/client_map.h"

ClientMap::ClientMap(int width, int height, int grid_size) : width(width),
                    height(height) {
    real_width = width*grid_size;
    real_height = height*grid_size;
}

ClientMap::ClientMap() : width(0),
                         height(0),
                         real_width(0),
                         real_height(0) {
}

int ClientMap::getGridSize() {
    return grid_size;
}

bool ClientMap::outOfHorizontalBounds(int x_pos) {
    return x_pos < 0 || x_pos > real_width;
}

bool ClientMap::outOfVerticalBounds(int y_pos) {
    return y_pos < 0 || y_pos > real_height;
}

bool ClientMap::wallAtGrid(std::pair<int, int> grid_coordinates) {
    int x_pos = grid_coordinates.first;
    int y_pos = grid_coordinates.second;
    if (x_pos < 0)
        x_pos = 0;
    if (y_pos < 0)
        y_pos = 0;
    x_pos *= grid_size;
    y_pos *= grid_size;
    std::pair<int, int> coordinates(x_pos, y_pos);
    if (drawables_by_position.find(coordinates) == drawables_by_position.end())
        return false;
    Drawable& drawable = drawables_by_position.at(coordinates);
    int object_type = drawable.getObjectType();
    return ImageManager::objectIsWall(object_type);
}

int ClientMap::getMaxDistance() {
    return (int) (Calculator::calculateDistance(real_width, real_height));
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
    return std::ref(drawables_by_position.at(coordinates));
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

void ClientMap::getMapInfoForObject(ObjectInfo& object_info,
                                    int x_pos,
                                    int y_pos,
                                    int x_factor,
                                    int y_factor) {

    int x_coord = x_pos/grid_size*grid_size + x_factor*grid_size;
    int y_coord = y_pos/grid_size*grid_size + y_factor*grid_size;
    if (x_coord < 0)
        x_coord = 0;
    if (y_coord < 0)
        y_coord = 0;
    std::pair<int, int> grid_coordinates{x_coord, y_coord};
    if (wallAtGrid(x_pos, y_pos, x_factor, y_factor))
        loadWallInfo(object_info, grid_coordinates);
}

void ClientMap::loadWallInfo(ObjectInfo& object_info,
                             std::pair<int, int> grid_coordinates) {
    Drawable drawable = drawables_by_position.at(grid_coordinates);
    object_info.setObjectType(drawable.getObjectType());
    object_info.setMapStartingPos(drawable.getMapPosition());
}

void ClientMap::putPlayerAt(std::pair<int, int> coord){
    player_coord = coord;
}

void ClientMap::addWalls(std::vector<std::pair<int,int>> walls,
                         std::vector<int> types) {
    int counter = 0;
    for (auto& wall : walls) {
        //printf("se pone una pared en : (%d, %d)\n", wall.first, wall.second);
        int type = types[counter];
        putDrawableAt(wall, type);
        ++counter;
    }
    //putDrawableAt(std::pair<int, int>(4,2), 0);
    //putDrawableAt(150,128,4);
    putDrawableAt(150,192, ENEMY_OFFICER);
    //putDrawableAt(400,350,6);
    //putDrawableAt(100,600,8);
    //putDrawableAt(750,100,9);
    //putDrawableAt(700,250,11);
}

void ClientMap::putDrawableAt(std::pair<int, int> coordinates, int object_type){
    Drawable drawable(object_type);
    coordinates.first*= grid_size;
    coordinates.second*= grid_size;
    drawables_by_position.insert(std::pair<std::pair<int, int>,
            Drawable>(coordinates,drawable));
}

void ClientMap::putDrawableAt(int x_pos, int y_pos, int object_type) {
    Drawable drawable(object_type);
    drawable.setMapPosition(x_pos, y_pos);
}

void ClientMap::moveObject(int object_id, std::pair<int, int> new_coordinates) {
    Drawable& drawable = objects.at(object_id);
    std::pair<int, int> current_coord = drawable.getMapPosition();
    drawables_by_position.erase(current_coord);
    new_coordinates.first*= grid_size;
    new_coordinates.second*= grid_size;
    drawable.setMapPosition(new_coordinates.first, new_coordinates.second);
    drawables_by_position.insert(std::pair<std::pair<int, int>,
            Drawable>(new_coordinates,drawable));
}

void ClientMap::moveObject(int object_id, int x_pos, int y_pos){
    if (objects.find(object_id) == objects.end())
        return;
    Drawable& drawable = objects.at(object_id);
    std::pair<int, int> current_coord = drawable.getMapPosition();
    drawables_by_position.erase(current_coord);
    drawable.setMapPosition(x_pos, y_pos);
    drawables_by_position.insert(std::pair<std::pair<int, int>,
            Drawable>(std::pair<int, int>{x_pos, y_pos},drawable));
}

int ClientMap::getWidth() {
    return real_width;
}

int ClientMap::getHeight() {
    return real_height;
}

std::vector<Drawable> ClientMap::getAllObjectsAndEnemies() {
    std::vector<Drawable> objects_vector;
    for (auto& pair : objects) {
        objects_vector.push_back(pair.second);
    }
    for (auto& pair : enemies) {
        objects_vector.push_back(pair.second);
    }
    return objects_vector;
}

void ClientMap::removeObject(int object_id) {
    if (objects.find(object_id) == objects.end())
        return;
    Drawable object = objects.at(object_id);
    objects.erase(object_id);
    std::pair<int, int> object_position = object.getMapPosition();
    drawables_by_position.erase(object_position);
}

Drawable& ClientMap::getObjectById(int object_id) {
    return objects.at(object_id);
}

void ClientMap::addObjectAt(int object_type,
                            int x_pos,
                            int y_pos) {
    putDrawableAt(x_pos, y_pos, object_type);

}

void ClientMap::updateUnlockedDoor(int object_id, int x_pos, int y_pos) {
    removeObject(object_id);
}

void ClientMap::updateRPGMissile(int object_id, int new_x, int new_y) {
}

void ClientMap::setRPGMissileExplosion(int object_id, int exp_x, int exp_y) {
    removeObject(object_id);
    putDrawableAt(exp_x, exp_y, EFFECT_EXPLOSION);
}

void ClientMap::setDimensions(int _width, int _height) {
    width = _width;
    height = _height;
    real_width = width * grid_size;
    real_height = height * grid_size;
}

void ClientMap::setObjectId(std::pair<int, int> coordinates, int object_id) {
    Drawable& drawable = drawables_by_position.at(coordinates);
    drawable.setId(object_id);
    int object_type = drawable.getObjectType();
    if (ImageManager::objectIsWall(object_type))
        walls.insert(std::pair<int, Drawable>{object_type, drawable});
    else
        objects.insert(std::pair<int, Drawable>{object_type, drawable});
}

void
ClientMap::addObjectAt(int object_type, int object_id, int x_pos, int y_pos) {
    Drawable drawable(object_type);
    drawable.setId(object_id);
    drawable.setMapPosition(x_pos, y_pos);
    objects.insert(std::pair<int, Drawable>{object_id, drawable});
    std::pair<int, int> coords{x_pos, y_pos};
    drawables_by_position.insert(std::pair<std::pair<int, int>,Drawable>
            {coords, drawable});
}

void ClientMap::addPlayerSpawnAt(int x_pos, int y_pos) {
    player_spawns.emplace_back(x_pos, y_pos);
}

void ClientMap::addPlayers(int number_of_players, int own_player_id) {
    for (int i = 0; i < number_of_players; ++i) {
        if (i == own_player_id)
            continue;
        std::pair<int, int> player_pos = player_spawns[i];
        putEnemyAt(player_pos.first, player_pos.second, ENEMY_GUARD, i);
    }
}

void ClientMap::putEnemyAt(int x_pos, int y_pos, int object_type, int id) {
    Drawable enemy(object_type);
    enemy.setId(id);
    enemy.setMapPosition(x_pos, y_pos);
    enemies.insert(std::pair<int, Drawable>(id, enemy));
}

std::pair<int, int> ClientMap::getSpawnPositionForPlayer(int player_id) {
    return player_spawns[player_id];
}

void ClientMap::erasePlayer(int player_id) {
    enemies.erase(player_id);
}

void ClientMap::updateTotalPlayers(int _total_players) {
    total_players = _total_players;
}

void ClientMap::respawnPlayer(int player_id) {
    std::pair<int, int> respawn_position = player_spawns[player_id];
    Drawable& enemy = enemies.at(player_id);
    enemy.setMapPosition(respawn_position.first, respawn_position.second);
}

void ClientMap::changeEnemyImage(int player_id, int weapon) {
    Drawable& current_drawable = enemies.at(player_id);
    int object_type = ImageManager::getImageNumberFromWeapon(weapon);
    Drawable new_drawable(object_type);
    new_drawable.setMapPosition(current_drawable.getMapPosition());
    new_drawable.setId(player_id);
    enemies.erase(player_id);
    enemies.insert(std::pair<int, Drawable>(player_id, new_drawable));
}

void ClientMap::updateEnemiesSprites() {
    for (auto& pair : enemies) {
        Drawable& enemy = pair.second;
        enemy.setNextMovingSprite();
    }
}
/*
void ClientMap::updateEnemySprite(int enemy_id) {

}
*/

void ClientMap::addEnemies(int own_player_id) {
    for (int i = 0; i < total_players; ++i) {
        if (i == own_player_id)
            continue;
        std::pair<int, int> player_coords = player_spawns[i];
        int player_x = player_coords.first;
        int player_y = player_coords.second;
        putEnemyAt(player_x, player_y, ENEMY_GUARD, i);
    }
}
