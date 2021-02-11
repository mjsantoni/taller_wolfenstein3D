//
// Created by andy on 7/2/21.
//

#ifndef TP_WOLFENSTEIN_IMAGE_MANAGER_H
#define TP_WOLFENSTEIN_IMAGE_MANAGER_H

#include <string>
#include <client/graphics/images.h>
#include <client/graphics/item_types.h>

class ImageManager {
public:
    static int getImageNumberFromName(std::string name);
    static bool objectIsWall(int object_type);
    static int getImageNumberFromWeapon(int weapon_number);
    static int getItemTypeForObject(int object_type);
};


#endif //TP_WOLFENSTEIN_IMAGE_MANAGER_H
