//
// Created by andy on 7/2/21.
//

#include <vector>
#include <iostream>
#include "client/game/image_manager.h"

#define WEAPON_ENEMY_DELTA 17

int ImageManager::getImageNumberFromName(std::string name) {
    if (name == "wood_wall")
        return BROWN_WALL;
    if (name == "stone_wall")
        return GRAY_WALL;
    if (name == "blue_wall")
        return BLUE_WALL;
    if (name == "fake_wall")
        return STONE_WALL;
    if (name == "unlocked_door")
        return SILVER_DOOR;
    if (name == "locked_door")
        return SILVER_DOOR;
    if (name == "crown")
        return ITEM_CROWN;
    if (name == "rpg_gun")
        return ITEM_ROCKET_LAUNCHER;
    if (name == "chain_gun")
        return ITEM_CHAIN_CANNON;
    if (name == "machine_gun")
        return ITEM_MACHINE_GUN;
    if (name == "bullets")
        return ITEM_BULLETS;
    if (name == "chest")
        return ITEM_CHEST;
    if (name == "cross")
        return ITEM_CROSS;
    if (name == "cup")
        return ITEM_CUP;
    if (name == "table")
        return MISC_TABLE;
    if (name == "barrel")
        return MISC_BARREL;
    if (name == "medical")
        return ITEM_MEDICAL_KIT;
    if (name == "food")
        return ITEM_FOOD;
    return ITEM_KEY;
}

bool ImageManager::objectIsWall(int object_type) {
    return object_type == GRAY_WALL || object_type == BLUE_WALL || object_type
    == BROWN_WALL || object_type == STONE_WALL || object_type == SILVER_DOOR;
}

int ImageManager::getImageNumberFromWeapon(int weapon_number) {
    return weapon_number + WEAPON_ENEMY_DELTA;
}

int ImageManager::getShootingAnimationForWeapon(int weapon_number) {
    if (weapon_number == WEAPON_MACHINE_GUN)
        return 3;
    return 2;
}

void ImageManager::getMovingAnimationForEnemy(Drawable& drawable,
                                              int current_animation) {
    int object_type = drawable.getObjectType();
    std::vector<int> possible_animations =
            getMovingAnimationsForEnemy(object_type);
    if (current_animation == possible_animations[possible_animations.size()-1])
        drawable.setSpriteAnimationNo(possible_animations[0]);
    else {
        bool animation_found = false;
        for (auto& animation : possible_animations) {
            if (animation > current_animation) {
                drawable.setSpriteAnimationNo(animation);
                animation_found = true;
                break;
            }
        }
        if (!animation_found)
            drawable.setSpriteAnimationNo(possible_animations[0]);
    }
    //std::cout << "El enemigo se mueve, animacion: " << drawable.getSpriteAnimationNo() << std::endl;
}

std::vector<int> ImageManager::getMovingAnimationsForEnemy(int object_type) {
    if (object_type == ENEMY_DOG)
        return {1, 4, 7};
    return std::vector<int>{0, 1, 4, 7};
}

void ImageManager::getAttackingAnimationForEnemy(Drawable& enemy) {
    int current_animation = enemy.getSpriteAnimationNo();
    if (current_animation == 3)
        enemy.setSpriteAnimationNo(6);
    else
        enemy.setSpriteAnimationNo(3);
    std::cout << "El enemigo ataca, animacion: " << enemy.getSpriteAnimationNo() << std::endl;
}

void ImageManager::getDyingAnimationForEnemy(Drawable &enemy) {
    enemy.setSpriteAnimationNo(8); // HAY MAS
    std::cout << "El enemigo muere, animacion: " << enemy.getSpriteAnimationNo() << std::endl;
}
