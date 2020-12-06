//
// Created by andy on 4/12/20.
//

#include "client/positionable_handler.h"
#include "client/wall_3d.h"
#include "client/enemy.h"

Positionable PositionableHandler::createPositionableFromType(int object_type,
                                                       std::string image_name) {
    switch (object_type) {
        case 1:
            return Wall_3d(image_name);
        case 2:
            return Enemy("enemy1", image_name);
        default:
            return Wall_3d(image_name);
    }
}
