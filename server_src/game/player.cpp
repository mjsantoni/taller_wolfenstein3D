#include <functional>
#include "server/game/player.h"
#include <ctgmath>

#define EXTRA_GUN_VECTOR_SIZE 1

Player::Player(int _id, int _max_bullets, int _max_hp, int _bullets, int _max_lives, ConfigParser& cp) :
    id(_id), angle(0),
    max_hp(_max_hp), hp(_max_hp), max_bullets(_max_bullets),
    bullets(_bullets), default_bullets(_bullets), total_keys(0), lives(_max_lives) {

  guns.resize(TOTAL_GUNS + EXTRA_GUN_VECTOR_SIZE);
  std::vector<double> knife_stats = cp.getSpecificGun("knife");
  std::vector<double> pistol_stats = cp.getSpecificGun("pistol");
  guns[KNIFE] = Gun("knife", -1, knife_stats[0], knife_stats[1], knife_stats[2], knife_stats[3]);
  guns[PISTOL] = Gun("pistol", -1, pistol_stats[0], pistol_stats[1], pistol_stats[2], pistol_stats[3]);
  equipped_weapon = guns[PISTOL];
}

Gun& Player::getGun() { return equipped_weapon; }

Gun& Player::getGun(int hotkey) { return guns[hotkey]; }

int Player::getID() { return id; }

double Player::getAngle() { return angle; }

int Player::getKeys() { return total_keys; }

int Player::getBullets() { return bullets; }

int Player::getLives() { return lives; }

/* ADDERS */

void Player::addHp(int hp_given) {
  if (hp + hp_given >= max_hp) hp = max_hp;
  else hp += hp_given;
}

void Player::addPoints(int points_given) {
  points += points_given;
}

void Player::addGun(Gun gun) {
  guns[getGunHotkey(gun.getType())] = gun;
}

void Player::addBullets(int added_bullets) {
  if (bullets == 0) {
    changeGun(previous_weapon);
  }
  if (bullets + added_bullets >= max_bullets) bullets = max_bullets;
  else bullets += added_bullets;
}

void Player::addKey() {
  total_keys++;
}

void Player::addAngle(double _angle) {
  angle += _angle;
  if (angle > 2 * M_PI) angle -= 2 * M_PI;
  if (angle < 0) angle += 2 * M_PI;
}

/* STATS SUB */

void Player::reduceAmmo(int _bullets) {
  if (equipped_weapon.getType() == "knife") { return; }
  bullets -= _bullets;
  if (bullets == 0) { changeGun(KNIFE); }
}

int Player::reduceHP(int damage) {
  int hp_reduced = 0;
  if (hp - damage <= 0) {
    hp_reduced = hp; //return hp
    hp = 0;
  } else {
    hp_reduced = damage;
    hp -= damage;
  }
  return hp_reduced;
}

/* CHECKERS */

bool Player::isFullHP() const { return hp == max_hp; }

bool Player::canPickUpBlood() const { return hp < 11; }

bool Player::hasMaxBullets() const { return bullets >= max_bullets; }

bool Player::noAmmoLeft() const { return bullets <= 0; }

bool Player::isDead() { return hp <= 0; }

bool Player::hasGun(const std::string& gun_type) {
  for (auto& gun : guns) {
    if (gun.getType() == gun_type) return true;
  }
  return false;
}

bool Player::hasGun(int hotkey) {
  for (int i = 0; i < guns.size(); i++) {
    if (guns[i].getType() == guns[hotkey].getType()) return true;
  }
  return false;
}

bool Player::hasLives() { return lives > 0; }

/* KEYS */

bool Player::useKey() {
  if (total_keys == 0) return false;
  total_keys--;
  return true;
}

/* OTHERS */

int Player::changeGun(int hotkey) {
  if (hotkey == 0 || guns[hotkey].getType() == "null") {
    return getGunHotkey(equipped_weapon.getType());
  }
  previous_weapon = getGunHotkey(equipped_weapon.getType());
  equipped_weapon = guns[hotkey];
  return hotkey;
}

int Player::getGunHotkey(const std::string& type) {
  if (type == "chain_gun") return CHAIN_GUN;
  else if (type == "machine_gun") return MACHINE_GUN;
  else if (type == "rpg_gun") return RPG_GUN;
  else if (type == "pistol") return PISTOL;
  else if (type == "knife") return KNIFE;
  else return 0;
}

bool Player::dieAndRespawn() {
  lives--;
  if (lives > 0) {
    hp = max_hp;
    changeGun(PISTOL); // Cambia a pistol por defecto al morir
    previous_weapon = PISTOL;
    bullets = default_bullets;
    return true; // respawnAtOriginalLoc()
  } else {
    return false;
  }
}

std::pair<std::string, bool> Player::getDropsFromDeath() {
  std::pair<std::string, bool> drops(std::make_pair("pistol", false));
  // Par: String = tipo de arma y bool es si tiene llave o no
  for (auto& gun : guns) {
    if (gun.getType() != "null" && gun.getType() != "knife" &&
        gun.getType() != "pistol") {
      drops.first = gun.getType();
      guns[getGunHotkey(drops.first)] = Gun(); // Elimina el arma que va a dropear (reemplaza por nula)
    }
  }
  drops.second = useKey();
  return drops;
}







