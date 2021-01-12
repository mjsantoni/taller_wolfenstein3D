#include "server/game/pickup_handler.h"
#include "server/entities/barrel.h"
#include "server/entities/bullets.h"
#include "server/entities/treasure.h"
#include "server/entities/hp_item.h"
#include "server/entities/gun.h"
#include "server/entities/key.h"

#include "server/entities/table.h"
#include "server/entities/wall.h"

PickUpHandler::PickUpHandler(std::string config_path) : configParser(config_path) {}
PickUpHandler::~PickUpHandler() {}

void PickUpHandler::pickUp(Positionable& item, Player& player) {
    if (item.getCategory() == "treasure") pickUpTreasure(item.getType(), player);
    else if (item.getCategory() == "hp_item") pickUpHpItem(item.getType(), player);
    else if (item.getCategory() == "gun") pickUpGun(item.getType(), player);
    else if (item.getCategory() == "bullets") pickUpBullets(item.getType(), player);
    else if (item.getCategory() == "key") pickUpKey(item.getType(), player);
}

void PickUpHandler::pickUpTreasure(std::string id, Player &player) {
    //Treasure item(config[id], id);
    player.addPoints(10);
}

void PickUpHandler::pickUpHpItem(std::string id, Player &player) {
    //HPItem item(config[id], id);
    player.addHp(10);
}

void PickUpHandler::pickUpGun(std::string id, Player &player) {
    //Gun gun(muchas cosas, id);
    //player.addGun(gun);
}

void PickUpHandler::pickUpBullets(std::string id, Player &player) {
    //Bullets bullets(config[id], id);
    player.addBullets(5);
}

void PickUpHandler::pickUpKey(std::string id, Player &player) {
    Key key;
    player.addKey(key);
}
