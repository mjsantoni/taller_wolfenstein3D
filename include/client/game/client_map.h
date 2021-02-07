//
// Created by andy on 25/11/20.
//

#ifndef TP_WOLFENSTEIN_CLIENT_MAP_H
#define TP_WOLFENSTEIN_CLIENT_MAP_H

#include <unordered_map>
#include <vector>
#include <map>
#include "client/object_info_provider.h"
#include "client/drawable.h"
#include "client/graphics/images.h"
#include "image_manager.h"
#include "client/calculator.h"

#define GRID_SIZE 64

class ClientMap {
private:
    std::map<std::pair<int, int>, Drawable> drawables_by_position;
    //std::map<std::pair<int, int>, Drawable> objects_by_position;
    //std::map<std::string, std::pair<int, int>> enemies_by_position;
    std::pair<int, int> player_coord;
    std::map<int, Drawable> walls;
    std::map<int, Drawable> objects;
    std::map<int, Drawable> enemies;
    int grid_size = GRID_SIZE;
    int width;
    int height;
    int real_width;
    int real_height;
    void loadWallInfo(ObjectInfo& object_info,
                      std::pair<int, int> grid_coordinates);
public:
    ClientMap(int width, int height, int grid_size);
    ClientMap();
    //bool OnLoad(char* File);
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
    void getMapInfoForObject(ObjectInfo& object_info, int x_pos, int y_pos,
                             int x_factor, int y_factor);
    void putPlayerAt(std::pair<int, int> coord);
    void addWalls(std::vector<std::pair<int,int>> walls,std::vector<int> types);
    void putDrawableAt(std::pair<int, int> coordinates, int object_type);
    void putDrawableAt(int x_pos, int y_pos, int object_type);
    void setObjectId(std::pair<int, int> coordinates, int object_id);
    std::vector<Drawable> getAllObjects();
    void removeObject(int object_id);
    void moveObject(int object_id, int new_x, int new_y);
    Drawable& getObjectById(int object_id);
    void addObjectAt(int object_type, int x_pos, int y_pos);
    void addObjectAt(int object_type, int object_id, int x_pos, int y_pos);
    void updateUnlockedDoor(int object_id, int x_pos, int y_pos);
    void updateRPGMissile(int object_id, int new_x, int new_y);
    void setRPGMissileExplosion(int object_id, int exp_x, int exp_y);
    void setDimensions(int _width, int _height, int _grid_size);
    void moveObject(int object_id, std::pair<int, int> new_coordinates);
};


#endif //TP_WOLFENSTEIN_CLIENT_MAP_H
