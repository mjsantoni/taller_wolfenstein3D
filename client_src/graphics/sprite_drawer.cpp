//
// Created by andy on 11/2/21.
//

#include <vector>
#include "client/graphics/sprite_drawer.h"

std::pair<int, int> SpriteDrawer::findLimitsForObject(int object_type,
                                       int& current_width,
                                       int& current_height) {
    std::pair<int, int> limits_activated{0, 0};
    int item_type = ImageManager::getItemTypeForObject(object_type);
    int min_width = findMinWidthForObject(item_type);
    int min_height = findMinHeightForObject(item_type);
    int max_width = findMaxWidthForObject(item_type);
    int max_height = findMaxHeightForObject(item_type);
    current_width = (current_width < min_width) ? min_width : current_width;
    current_width = (current_width > max_width) ? max_width : current_width;
    current_height = (current_height < min_height) ? min_height :current_height;
    current_height = (current_height > max_height) ? max_height :current_height;
    if (current_width == max_width)
        limits_activated.first = 1;
    if (current_height == max_height)
        limits_activated.second = 1;
    return limits_activated;
}

int SpriteDrawer::findMinWidthForObject(int item_type) {
    switch (item_type) {
        case ITEM_TYPE_VERY_SMALL:
            return 30;
        case ITEM_TYPE_SMALL:
            return 40;
        case ITEM_TYPE_MEDIUM:
            return 80;
        case ITEM_TYPE_LARGE:
            return 50;
        case ITEM_TYPE_WEAPON:
            return 120;
        default:
            return 70;
    }
}

int SpriteDrawer::findMinHeightForObject(int item_type) {
    switch (item_type) {
        case ITEM_TYPE_VERY_SMALL:
            return 10;
        case ITEM_TYPE_SMALL:
            return 15;
        case ITEM_TYPE_MEDIUM:
            return 20;
        case ITEM_TYPE_LARGE:
            return 75;
        case ITEM_TYPE_WEAPON:
            return 25;
        default:
            return 20;
    }
}

int SpriteDrawer::findMaxWidthForObject(int item_type) {
    switch (item_type) {
        case ITEM_TYPE_VERY_SMALL:
            return 30;
        case ITEM_TYPE_SMALL:
            return 100;
        case ITEM_TYPE_MEDIUM:
            return 150;
        case ITEM_TYPE_LARGE:
            return 300;
        case ITEM_TYPE_WEAPON:
            return 225;
        default:
            return 150;
    }
}

int SpriteDrawer::findMaxHeightForObject(int item_type) {
    switch (item_type) {
        case ITEM_TYPE_VERY_SMALL:
            return 15;
        case ITEM_TYPE_SMALL:
            return 25;
        case ITEM_TYPE_MEDIUM:
            return 40;
        case ITEM_TYPE_LARGE:
            return 80;
        case ITEM_TYPE_WEAPON:
            return 40;
        default:
            return 80;
    }
}
