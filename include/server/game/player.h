#ifndef TP_WOLFENSTEIN_PLAYER_H
#define TP_WOLFENSTEIN_PLAYER_H

#include <string>
#include "positionable.h"
#include "server/entities/gun.h"
#include "server/entities/key.h"
#include <queue>
#include <vector>
#include "default_weapon.h"

class Player {
private:
    std::string name;
    int id;
    int max_bullets;
    int max_hp;
    int bullets;
    int hp;
    int points = 0;
    int lives;
    double angle;

    std::vector<Gun> guns;
    Gun knife;
    Gun pistol;
    Gun equipped_weapon;
    std::queue<Key> keys;

public:
    Player(std::string _name, int _id, int _max_bullets, int _max_hp, int _bullets); //parametros de config como hp faltan

    /* Getters */
    std::string getPlayerName();
    int getID();
    Gun& getGun();
    double getAngle();

    /* Stats ADD */
    void addHp(int hp_given);
    void addPoints(int points_given);
    void addGun(Gun gun);
    void addBullets(int added_bullets);
    void addKey(Key key);
    void addAngle(double _angle);

    /* Stats SUB */
    void reduceAmmo();
    bool reduceHP(int value);

    /* Others */
    bool areAnyKeysLeft();
    bool useKey();
    void pickUpKey(Key key);
    void equipWeapon(std::string id);

    void changeGun(int hotkey);


    /* Prohibe construccion y asignacion por copia. */
    //Player(const Player&) = delete;
    //Player& operator=(const Player&) = delete;

    /* Prohibe construccion y asignacion por movimiento. */
    //Player(Player&&) = delete;
    //Player& operator=(Player&&) = delete;
    bool isFullHP();

    bool canPickUpBlood();

    bool hasMaxBullets();

    bool hasGun(std::string gun_type);
};

#endif //TP_WOLFENSTEIN_CLIENT_PLAYER_H
