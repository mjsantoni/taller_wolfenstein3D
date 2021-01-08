//
// Created by andy on 4/12/20.
//

#ifndef TP_WOLFENSTEIN_ENEMY_H
#define TP_WOLFENSTEIN_ENEMY_H

#include "positionable.h"

class Enemy : public Positionable {
public:
    Enemy(std::string unique_name, std::string image_path);
};


#endif //TP_WOLFENSTEIN_CLIENT_ENEMY_H
