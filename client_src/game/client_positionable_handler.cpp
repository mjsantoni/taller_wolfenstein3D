//
// Created by andy on 4/12/20.
//

#include "client/client_positionable_handler.h"
#include "client/client_wall_3d.h"
#include "client/client_enemy.h"

ClientPositionable ClientPositionableHandler::createPositionableFromType(int object_type,
                                                       std::string image_name) {
    switch (object_type) {
        case 1:
            return ClientWall_3d(image_name);
        case 2:
            return ClientEnemy("enemy1", image_name);
        default:
            return ClientWall_3d(image_name);
    }
}
