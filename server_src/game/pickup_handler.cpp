#include "server/game/pickup_handler.h"
#include "server/entities/bullets.h"
#include "server/entities/treasure.h"
#include "server/entities/hp_item.h"
#include "server/entities/gun.h"
#include "server/entities/key.h"

PickUpHandler::PickUpHandler(std::string config_path, ScoreHandler& _sh) : configParser(config_path), scoreHandler(_sh) {}
PickUpHandler::~PickUpHandler() {}

bool PickUpHandler::pickUp(Positionable& item, Player& player) {
    if (item.getCategory() == "treasure")  return pickUpTreasure(item.getType(), item.getId(), player);
    else if (item.getCategory() == "hp_item")  return pickUpHpItem(item.getType(), item.getId(), player);
    else if (item.getCategory() == "gun")  return pickUpGun(item.getType(), item.getId(), player);
    else if (item.getCategory() == "bullets")  return pickUpBullets(player);
    else if (item.getCategory() == "key")  return pickUpKey(item.getId(), player);
    else return false;
}

bool PickUpHandler::pickUpTreasure(std::string type, int id, Player &player) {
    Treasure item(type, id, configParser.getSpecificCategory("treasure", type));
    player.addPoints(item.getPoints());
    scoreHandler.addTreasurePoints(player.getID(), item.getPoints());
    return true;
}

bool PickUpHandler::pickUpHpItem(std::string type, int id, Player &player) {
    if (player.isFullHP() || !player.canPickUpBlood()) return false;
    HPItem item(type, id, configParser.getSpecificCategory("hp_item", type));
    player.addHp(item.getHP());
    return true;
}

bool PickUpHandler::pickUpGun(std::string type, int id, Player &player) {
    if (player.hasGun(type)) return false;
    std::vector<double> gun_stats = configParser.getSpecificGun(type);
    Gun gun(type, id, gun_stats[0], gun_stats[1], gun_stats[2], gun_stats[3]);
    player.addGun(gun);
    return true;
}

bool PickUpHandler::pickUpBullets(Player &player) {
    if (player.hasMaxBullets()) return false;
    player.addBullets(configParser.getSpecificCategory("bullets", "bullets"));
    return true;
}

bool PickUpHandler::pickUpKey(int id, Player &player) {
    Key key(id);
    player.addKey(key);
    return true;
}
