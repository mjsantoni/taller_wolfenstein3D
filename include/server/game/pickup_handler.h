#ifndef TP_WOLFENSTEIN_PICKUP_HANDLER_H
#define TP_WOLFENSTEIN_PICKUP_HANDLER_H

#include "server/entities/positionable.h"
#include "server/game/player.h"
#include "common/config_parser.h"
#include "server/game/score_handler.h"

class PickUpHandler {
 private:
  ConfigParser configParser;
  ScoreHandler& scoreHandler;

 public:
  PickUpHandler(const std::string& config_path, ScoreHandler& _sh);

  bool pickUp(Positionable& item, Player& player);
  bool pickUpTreasure(const std::string& type, int id, Player& player);
  bool pickUpHpItem(const std::string& type, int id, Player& player);
  bool pickUpGun(const std::string& type, int id, Player& player);
  bool pickUpBullets(Player& player, const std::string& type);
  bool pickUpKey(int id, Player& player);

  ~PickUpHandler();

};

#endif //TP_WOLFENSTEIN_PICKUP_HANDLER_H
