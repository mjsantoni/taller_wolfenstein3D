//
// Created by andy on 4/12/20.
//

#include "client/Enemy.h"

Enemy::Enemy(std::string unique_name, std::string image_path):
        Positionable("Enemy", 2, true, image_path, unique_name) {
}
