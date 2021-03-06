//
// Created by andy on 7/2/21.
//

#ifndef TP_WOLFENSTEIN_IMAGE_MANAGER_H
#define TP_WOLFENSTEIN_IMAGE_MANAGER_H

#include <string>
#include <client/graphics/images.h>
#include <common/weapons.h>
#include <client/drawable.h>

class ImageManager {
 public:
  static int getImageNumberFromName(std::string name);
  static bool objectIsWall(int object_type);
  static bool objectIsDoor(int object_type);
  static bool objectIsAmmoRelated(int object_type);
  static int getImageNumberFromWeapon(int weapon_number);
  static int getAttackingAnimationForWeapon(int weapon_number);
  static std::vector<int> getMovingAnimationsForEnemy(int object_type);
  static void setDyingAnimationForEnemy(Drawable& enemy);
  static void setAttackingAnimationForEnemy(Drawable& enemy);
  static void setMovingAnimationForEnemy(Drawable& drawable,
                                         int current_animation);
  static int getWeaponNumberFromEnemy(int enemy_type);
};

#endif //TP_WOLFENSTEIN_IMAGE_MANAGER_H
