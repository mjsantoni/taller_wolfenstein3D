//
// Created by andy on 11/2/21.
//

#include <client/graphics/item_types.h>
#include <client/game/image_manager.h>

#ifndef TP_WOLFENSTEIN_SPRITE_DRAWER_H
#define TP_WOLFENSTEIN_SPRITE_DRAWER_H

class SpriteDrawer {
private:
public:

    std::pair<int, int> static findLimitsForObject(int object_type, int &current_width,
                        int &current_height);
    static int findMinWidthForObject(int item_type);
    static int findMinHeightForObject(int item_type);
    static int findMaxWidthForObject(int item_type);
    static int findMaxHeightForObject(int item_type);
};


#endif //TP_WOLFENSTEIN_SPRITE_DRAWER_H
