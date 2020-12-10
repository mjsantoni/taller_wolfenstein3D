//
// Created by andy on 4/12/20.
//

#ifndef TP_WOLFENSTEIN_CLIENT_ENEMY_H
#define TP_WOLFENSTEIN_CLIENT_ENEMY_H

#include "client_positionable.h"

class ClientEnemy : public ClientPositionable {
public:
    ClientEnemy(std::string unique_name, std::string image_path);
};


#endif //TP_WOLFENSTEIN_CLIENT_ENEMY_H
