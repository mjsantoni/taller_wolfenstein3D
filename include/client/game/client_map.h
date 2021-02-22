//
// Created by andy on 25/11/20.
//

#ifndef TP_WOLFENSTEIN_CLIENT_MAP_H
#define TP_WOLFENSTEIN_CLIENT_MAP_H

#include <unordered_map>
#include <vector>
#include <map>
#include <set>
#include "client/object_info_provider.h"
#include "client/drawable.h"
#include "client/graphics/images.h"
#include "client/graphics/effects.h"
#include "image_manager.h"
#include "client/calculator.h"
#include "effects_handler.h"
#include "client_map_board.h"

#define GRID_SIZE 64

class ClientMap {
private:
    ClientMapBoard board;
    std::map<std::pair<int, int>, Drawable> drawables_by_position;
    //std::map<std::pair<int, int>, Drawable> objects_by_position;
    //std::map<std::string, std::pair<int, int>> enemies_by_position;
    std::pair<int, int> player_coord;
    std::map<int, Drawable> walls;
    std::map<int, Drawable> objects;
    std::map<int, Drawable> enemies;
    std::map<int, Drawable> effects;
    std::vector<std::pair<int, int>> player_spawns;
    std::set<int> enemies_to_swipe;
    std::set<int> enemies_to_respawn;
    EffectsHandler effects_handler;
    int grid_size = GRID_SIZE;
    int width;
    int height;
    int real_width;
    int real_height;
    int total_players = 0;
    double max_distance;
    void putEnemyAt(int x_pos, int y_pos, int object_type, int id);
public:
    ClientMap(int width, int height, int grid_size);
    ClientMap();
    //bool OnLoad(char* File);
    int getGridSize();
    bool outOfVerticalBounds(int y_pos);
    bool outOfHorizontalBounds(int x_pos);
    int getMaxDistance();
    int getWidth();
    int getHeight();
    bool wallAtGrid(int x_pos, int y_pos, int x_factor, int y_factor);
    void getMapInfoForWall(RayInfo& ray_info, int x_pos, int y_pos,
                           int x_factor, int y_factor);
    void putWallAt(std::pair<int, int> coordinates, int object_type);
    std::vector<Drawable> getAllDrawables();
    void removeObject(int object_id);
    void moveEnemy(int object_id, int new_x, int new_y);
    Drawable& getObjectById(int object_id);
    void putObjectAt(int object_type, int x_pos, int y_pos);
    void putObjectAt(int object_id, int object_type, int x_pos, int y_pos);
    void updateUnlockedDoor(int object_id, int x_pos, int y_pos);
    void updateRPGMissile(int object_id, int new_x, int new_y);
    double setRPGMissileExplosion(int object_id, int exp_x, int exp_y);
    void setDimensions(int _width, int _height);
    void addPlayerSpawnAt(int x_pos, int y_pos);
    void addPlayers(int number_of_players, int own_player_id);
    std::pair<int, int> getSpawnPositionForPlayer(int player_id);
    void updateTotalPlayers(int _total_players);
    void respawnPlayer(int player_id);
    void changeEnemyImage(int player_id, int weapon);
    void updateEnemiesSprites();
    void addEnemies(int own_player_id);
    void addObjectId(int object_id, int x_pos, int y_pos);
    void updateEvents();
    int getObjectTypeFromId(int object_id);
    void killPlayer(int player_id);
    void setEnemyAttacking(int enemy_id);
    void setBloodEffectForEnemy(int enemy_id);
    int getEnemyTypeFromId(int enemy_id);
    double getEnemyDistanceRatio(int enemy_id);
    bool isLastPlayerStanding();
    int getEnemiesAlive();
    void processRPGMissile(int object_id, int new_x, int new_y);
    void createRPGMissile(int object_id, int new_x, int new_y);

    void updatePlayerPosition(int x_pos, int y_pos);
};

#endif //TP_WOLFENSTEIN_CLIENT_MAP_H
