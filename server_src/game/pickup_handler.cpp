#include "server/game/pickup_handler.h"
#include "server/entities/bullets.h"
#include "server/entities/treasure.h"
#include "server/entities/hp_item.h"
#include "server/entities/gun.h"
#include "server/entities/key.h"

PickUpHandler::PickUpHandler(std::string config_path) : configParser(config_path) {}
PickUpHandler::~PickUpHandler() {}

void PickUpHandler::pickUp(Positionable& item, Player& player) {
    if (item.getCategory() == "treasure") pickUpTreasure(item.getType(), player);
    else if (item.getCategory() == "hp_item") pickUpHpItem(item.getType(), player);
    else if (item.getCategory() == "gun") pickUpGun(item.getType(), player);
    else if (item.getCategory() == "bullets") pickUpBullets(item.getType(), player);
    else if (item.getCategory() == "key") pickUpKey(item.getType(), player);
}

void PickUpHandler::pickUpTreasure(std::string type, Player &player) {
    Treasure item(type, -1, configParser.getSpecificCategory("treasure", type));
    player.addPoints(item.getPoints());
}

void PickUpHandler::pickUpHpItem(std::string type, Player &player) {
    HPItem item(type, -1, configParser.getSpecificCategory("hp_item", type));
    player.addHp(item.getHP());
}

void PickUpHandler::pickUpGun(std::string type, Player &player) {
    std::vector<double> gun_stats = configParser.getSpecificGun(type);
    Gun gun(type, -1, gun_stats[0], gun_stats[1], gun_stats[2]);
    player.addGun(gun);
}

void PickUpHandler::pickUpBullets(std::string type, Player &player) {
    player.addBullets(configParser.getBullets());
}

void PickUpHandler::pickUpKey(std::string id, Player &player) {
    Key key;
    player.addKey(key);
}
