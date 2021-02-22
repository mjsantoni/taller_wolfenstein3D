#ifndef TP_WOLFENSTEIN_BOTS_MANAGER_H
#define TP_WOLFENSTEIN_BOTS_MANAGER_H

#include "server/entities/positionable.h"
#include "server/lua/lua_bot.h"
#include "server/game/map.h"
#include "server/utils/probability.h"
#include <mutex>
#include <vector>
#include <zconf.h>

class BotsManager {
 private:
  std::vector<LuaBot*> bots;
  std::condition_variable cv;
  SharedQueue<Event>& sharedQueue;
  Probability probability;

 public:
  BotsManager(SharedQueue<Event>& sq);

  void addBot(Player& player, double angle_turn);

  void sendMapToBot(LuaBot* bot, Map& map, std::vector<Player>& players);

  void releaseBots(Map& map, std::vector<Player>& players);

  void destroyBots();

  ~BotsManager();
};

#endif //TP_WOLFENSTEIN_BOTS_MANAGER_H
