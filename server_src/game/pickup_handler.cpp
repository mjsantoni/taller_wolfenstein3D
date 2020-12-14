#include "server/pickup_handler.h"
#include "server/barrel.h"
#include "server/bullets.h"
#include "server/chain_gun.h"
#include "server/chest.h"
#include "server/cross.h"
#include "server/crown.h"
#include "server/food.h"
#include "server/goblet.h"
#include "server/key.h"
#include "server/machine_gun.h"
#include "server/medikit.h"
#include "server/rocket_launcher.h"
#include "server/table.h"
#include "server/wall.h"

PickUpHandler::PickUpHandler() {}
PickUpHandler::~PickUpHandler() {}

void PickUpHandler::pickUp(Positionable& item, Player& player) {
    if (item.getType() == "treasure") pickUpTreasure(item.getId(), player);
    else if (item.getType() == "hp_item") pickUpHpItem(item.getId(), player);
    else if (item.getType() == "gun") pickUpGun(item.getId(), player);
    else if (item.getType() == "bullets") pickUpBullets(item.getId(), player);
    else if (item.getType() == "key") pickUpKey(item.getId(), player);
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
