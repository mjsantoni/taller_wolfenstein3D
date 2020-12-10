//
// Created by andy on 4/12/20.
//

#include "client/client_enemy.h"

ClientEnemy::ClientEnemy(std::string unique_name, std::string image_path):
        ClientPositionable("Enemy", 2, true, image_path, unique_name) {
}
