#include "server/game/pickup_handler.h"
#include "server/entities/bullets.h"
#include "server/entities/treasure.h"
#include "server/entities/hp_item.h"
#include "server/entities/gun.h"
#include "server/entities/key.h"

PickUpHandler::PickUpHandler(std::string config_path) : configParser(config_path) {}
PickUpHandler::~PickUpHandler() {}

bool PickUpHandler::pickUp(Positionable& item, Player& player) {
    if (item.getCategory() == "treasure")  return pickUpTreasure(item.getType(), player);
    else if (item.getCategory() == "hp_item")  return pickUpHpItem(item.getType(), player);
    else if (item.getCategory() == "gun")  return pickUpGun(item.getType(), player);
    else if (item.getCategory() == "bullets")  return pickUpBullets(item.getType(), player);
    else if (item.getCategory() == "key")  return pickUpKey(item.getType(), player);
    else return false;
}

bool PickUpHandler::pickUpTreasure(std::string type, Player &player) {
    Treasure item(type, -1, configParser.getSpecificCategory("treasure", type));
    player.addPoints(item.getPoints());
    return true;
}

bool PickUpHandler::pickUpHpItem(std::string type, Player &player) {
    if (player.isFullHP() || !player.canPickUpBlood()) return false;
    HPItem item(type, -1, configParser.getSpecificCategory("hp_item", type));
    player.addHp(item.getHP());
    return true;
}

bool PickUpHandler::pickUpGun(std::string type, Player &player) {
    if (player.hasGun(type)) return false;
    std::vector<double> gun_stats = configParser.getSpecificGun(type);
    Gun gun(type, -1, gun_stats[0], gun_stats[1], gun_stats[2]);
    player.addGun(gun);
    return true;
}

bool PickUpHandler::pickUpBullets(std::string type, Player &player) {
    if (player.hasMaxBullets()) return false;
    player.addBullets(configParser.getBullets());
    return true;
}

bool PickUpHandler::pickUpKey(std::string id, Player &player) {
    Key key;
    player.addKey(key);
    return true;
}
