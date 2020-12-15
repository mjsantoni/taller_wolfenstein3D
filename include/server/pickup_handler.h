#ifndef TP_WOLFENSTEIN_PICKUP_HANDLER_H
#define TP_WOLFENSTEIN_PICKUP_HANDLER_H
#include "positionable.h"
#include "player.h"

class PickUpHandler {
private:

public:
    PickUpHandler();

    void pickUp(Positionable& item, Player& player);
    void pickUpTreasure(std::string id, Player& player);
    void pickUpHpItem(std::string id, Player& player);
    void pickUpGun(std::string id, Player& player);
    void pickUpBullets(std::string id, Player& player);
    void pickUpKey(std::string id, Player& player);

    ~PickUpHandler();

};


#endif //TP_WOLFENSTEIN_PICKUP_HANDLER_H
