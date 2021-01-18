#ifndef TP_WOLFENSTEIN_PICKUP_HANDLER_H
#define TP_WOLFENSTEIN_PICKUP_HANDLER_H

#include "positionable.h"
#include "player.h"
#include "config_parser.h"

class PickUpHandler {
private:
    ConfigParser configParser;

public:
    PickUpHandler(std::string config_path);

    bool pickUp(Positionable& item, Player& player);
    bool pickUpTreasure(std::string type, int id, Player &player);
    bool pickUpHpItem(std::string type, int id, Player &player);
    bool pickUpGun(std::string type, int id, Player &player);
    bool pickUpBullets(Player &player);
    bool pickUpKey(int id, Player& player);

    ~PickUpHandler();

};


#endif //TP_WOLFENSTEIN_PICKUP_HANDLER_H
