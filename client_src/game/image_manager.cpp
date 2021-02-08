//
// Created by andy on 7/2/21.
//

#include "client/game/image_manager.h"
#define WEAPON_ENEMY_DELTA 15

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
    return ITEM_KEY;
}

bool ImageManager::objectIsWall(int object_type) {
    return object_type == GRAY_WALL || object_type == BLUE_WALL || object_type
    == BROWN_WALL || object_type == STONE_WALL || object_type == SILVER_DOOR;
}

int ImageManager::getImageNumberFromWeapon(int weapon_number) {
    return weapon_number + WEAPON_ENEMY_DELTA;
}
