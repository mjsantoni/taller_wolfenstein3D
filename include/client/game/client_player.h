//
// Created by andy on 25/11/20.
//

#ifndef TP_WOLFENSTEIN_CLIENT_PLAYER_H
#define TP_WOLFENSTEIN_CLIENT_PLAYER_H

#define TURN_VALUE M_PI/10

#include <string>
#include "client/graphics/sdl_texture.h"
#include "client/graphics/sdl_sprite.h"

class ClientPlayer {
public:
    ClientPlayer(std::string name);
    std::string getPlayerName();
    double getDirection();
    void updateDirection(int direction);
    double projectDirection(double direction_change_alpha);
    int getEquippedWeapon();
    int getLevel();
    int getScore();
    int getLives();
    int getHealth();
    int getAmmo();
    void updatePosition(int new_x, int new_y);
    int getId();
    void setId(int new_id);
    void updateScore(int extra_points);
    void updateHealth(int health_delta);
    void updateAmmo(int ammo_delta);
    void updateKeys(int keys_delta);
    void respawn();
    void changeWeapon(int weapon_number);
    std::pair<int, int> getMapPosition();
    void setMapPosition(std::pair<int, int> new_map_position);
    int getXPosition();
    int getYPosition();
private:
    int id = 0;
    std::string name;
    double direction = 0;
    int equipped_weapon = 2;
    int level = 6;
    int score = 10000;
    int lives = 5;
    int health = 100;
    int ammo = 200;
    int max_health;
    int max_ammo;
    int keys = 0;
    int weapons[5] = {1, 1, 0, 0, 0};
    std::pair<int, int> map_position;
    std::pair<int, int> respawn_position;
};


#endif //TP_WOLFENSTEIN_CLIENT_PLAYER_H
