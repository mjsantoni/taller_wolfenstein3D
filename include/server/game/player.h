#ifndef TP_WOLFENSTEIN_PLAYER_H
#define TP_WOLFENSTEIN_PLAYER_H

#include <string>
#include "positionable.h"
#include "server/entities/gun.h"
#include "server/entities/key.h"
#include <queue>
#include <vector>
#include "server/game/gun_hotkeys.h"

class Player {
private:
    std::string name;
    int id;
    int max_bullets;
    int max_hp;
    int bullets;
    int hp;
    int points = 0;
    int lives = 3; // add to config
    double angle;
    int previous_weapon;

    std::vector<Gun> guns;
    Gun equipped_weapon;
    std::queue<Key> keys;

    static int getGunHotkey(const std::string& type);

public:
    Player(std::string _name, int _id, int _max_bullets,
           int _max_hp, int _bullets); //parametros de config de las default gun falta

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
    int reduceHP(int value);

    /* Others */
    void changeGun(int hotkey);
    bool isFullHP() const;
    bool canPickUpBlood() const;
    bool hasMaxBullets() const;
    bool hasGun(std::string gun_type);
    bool noAmmoLeft() const;

    /* Keys */
    bool areAnyKeysLeft();
    int useKey();

    /* Prohibe construccion y asignacion por copia. */
    //Player(const Player& other) = delete;
    //Player& operator=(const Player& other) = delete;

    /* Prohibe construccion y asignacion por movimiento. */
    //Player(Player&&) = delete;
    //Player& operator=(Player&&) = delete;

    bool dieAndRespawn();

    std::pair<std::string, bool> getDrops();

    bool isDead();
};

#endif //TP_WOLFENSTEIN_CLIENT_PLAYER_H
