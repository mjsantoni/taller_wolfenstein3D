#ifndef TP_WOLFENSTEIN_PLAYER_H
#define TP_WOLFENSTEIN_PLAYER_H

#include <string>
#include "positionable.h"
#include "server/entities/gun.h"
#include "server/entities/key.h"
#include <queue>
#include <vector>
#include "server/game/gun_hotkeys.h"
#include "common/config_parser.h"

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
    int previous_weapon;
    int total_keys;

    std::vector<Gun> guns;
    Gun equipped_weapon;

    static int getGunHotkey(const std::string& type);

public:
    Player(std::string _name, int _id, int _max_bullets, int _max_hp, int _bullets, int _max_lives,
           ConfigParser &cp);

    /* Getters */
    std::string getPlayerName();
    Gun& getGun();
    Gun& getGun(int hotkey);
    int getID();
    double getAngle();
    int getKeys();
    int getBullets();
    int getLives();

    /* Stats ADD */
    void addHp(int hp_given);
    void addPoints(int points_given);
    void addGun(Gun gun);
    void addBullets(int added_bullets);
    void addKey();
    void addAngle(double _angle);

    /* Stats SUB */
    void reduceAmmo(int bullets);
    int reduceHP(int value);

    /* CHECKERS */
    bool isFullHP() const;
    bool canPickUpBlood() const;
    bool hasMaxBullets() const;
    bool noAmmoLeft() const;
    bool isDead();
    bool hasGun(const std::string& gun_type);
    bool hasGun(int hotkey);
    bool hasLives();

    /* Keys */
    bool useKey();

    /* OTHERS */
    int changeGun(int hotkey);
    bool dieAndRespawn();
    std::pair<std::string, bool> getDropsFromDeath();

    /* Prohibe construccion y asignacion por copia. */
    //Player(const Player& other) = delete;
    //Player& operator=(const Player& other) = delete;

    /* Prohibe construccion y asignacion por movimiento. */
    //Player(Player&&) = delete;
    //Player& operator=(Player&&) = delete;

};

#endif //TP_WOLFENSTEIN_CLIENT_PLAYER_H
