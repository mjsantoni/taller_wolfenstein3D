#ifndef TP_WOLFENSTEIN_PLAYER_H
#define TP_WOLFENSTEIN_PLAYER_H

#include <string>
#include <vector>
#include <queue>
#include "server/entities/positionable.h"
#include "server/entities/gun.h"
#include "server/entities/key.h"
#include "server/utils/gun_hotkeys.h"
#include "common/config_parser.h"

class Player {
 private:
  int id;
  int max_bullets;
  int max_hp;
  int bullets;
  int default_bullets;
  int hp;
  int points = 0;
  int lives;
  double angle;
  int previous_weapon;
  int total_keys;

  std::vector<Gun> guns;
  Gun equipped_weapon;

 public:

  Player(int _id, int _max_bullets, int _max_hp, int _bullets, int _max_lives, ConfigParser& cp);
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
  int getGunHotkey(const std::string& type);
  bool dieAndRespawn();
  std::pair<std::string, bool> getDropsFromDeath();
};

#endif //TP_WOLFENSTEIN_CLIENT_PLAYER_H
