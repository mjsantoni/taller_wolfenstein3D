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
    bool pickUpTreasure(std::string type, Player& player);
    bool pickUpHpItem(std::string type, Player& player);
    bool pickUpGun(std::string type, Player& player);
    bool pickUpBullets(std::string type, Player& player);
    bool pickUpKey(std::string id, Player& player);

    ~PickUpHandler();

};


#endif //TP_WOLFENSTEIN_PICKUP_HANDLER_H
