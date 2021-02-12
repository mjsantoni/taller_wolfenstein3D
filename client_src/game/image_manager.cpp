//
// Created by andy on 7/2/21.
//

#include "client/game/image_manager.h"
#include <client/graphics/item_types.h>

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

int ImageManager::getItemTypeForObject(int object_type) {
    if (object_type == ITEM_BULLETS || object_type == ITEM_KEY)
        return ITEM_TYPE_VERY_SMALL;
    if (object_type == ITEM_CUP || object_type == ITEM_CROWN)
        return ITEM_TYPE_SMALL;
    if (object_type == ITEM_CHEST || object_type == ITEM_CROSS)
        return ITEM_TYPE_MEDIUM;
    if (object_type == MISC_BARREL || object_type == MISC_TABLE)
        return ITEM_TYPE_LARGE;
    if (object_type == ENEMY_DOG)
        return ITEM_TYPE_ENEMY_DOG;
    if (object_type >= ENEMY_GUARD && object_type <= ENEMY_MUTANT)
        return ITEM_TYPE_ENEMY_HUMAN;
    return ITEM_TYPE_WEAPON;
}
/*
int ImageManager::getMovingSpriteAnimation(int object_type) {
    if (object_type == ITEM_BULLETS || object_type == ITEM_KEY)
        return ITEM_TYPE_VERY_SMALL;
    if (object_type == ITEM_CUP || object_type == ITEM_CROWN)
        return ITEM_TYPE_SMALL;
    if (object_type == ITEM_CHEST || object_type == ITEM_CROSS)
        return ITEM_TYPE_MEDIUM;
    if (object_type == MISC_BARREL || object_type == MISC_TABLE)
        return ITEM_TYPE_LARGE;
    if (object_type == ENEMY_DOG)
        return ITEM_TYPE_ENEMY_DOG;
    if (object_type >= ENEMY_GUARD && object_type <= ENEMY_MUTANT)
        return ITEM_TYPE_ENEMY_HUMAN;
    return ITEM_TYPE_WEAPON;
}
*/