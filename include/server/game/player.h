#ifndef TP_WOLFENSTEIN_PLAYER_H
#define TP_WOLFENSTEIN_PLAYER_H

#include <string>
#include "positionable.h"
#include "server/entities/gun.h"
#include "server/entities/key.h"
#include <queue>
#include <vector>
#include "default_weapon.h"
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
    int lives;
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
    bool reduceHP(int value);

    /* Others */
    void changeGun(int hotkey);
    bool isFullHP() const;
    bool canPickUpBlood() const;
    bool hasMaxBullets() const;
    bool hasGun(std::string gun_type);
    bool noAmmoLeft() const;

    /* Keys */
    bool areAnyKeysLeft();
    bool useKey();
    void pickUpKey(Key key);

    /* Prohibe construccion y asignacion por copia. */
    //Player(const Player&) = delete;
    //Player& operator=(const Player&) = delete;

    /* Prohibe construccion y asignacion por movimiento. */
    //Player(Player&&) = delete;
    //Player& operator=(Player&&) = delete;

};

#endif //TP_WOLFENSTEIN_CLIENT_PLAYER_H
