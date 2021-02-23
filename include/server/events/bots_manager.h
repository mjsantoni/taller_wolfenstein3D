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

  /* Constructor del manejador de bots. Recibe una queue de eventos
   * donde pushear los eventos creados por cada bot.
   */
  BotsManager(SharedQueue<Event>& sq);

  /* Añade un bot creandolo a partir del script y le da una referencia a
   * la clase Player de donde obtiene informacion actual de si mismo.
   */
  void addBot(Player& player, double angle_turn);

  void sendMapToBot(LuaBot* bot, Map& map, std::vector<Player>& players);

  /* Libera los bots de su condition variable de manera que puedan generar eventos
   * y accionar.*/
  void releaseBots(Map& map, std::vector<Player>& players);

  void destroyBots();

  ~BotsManager();
};

#endif //TP_WOLFENSTEIN_BOTS_MANAGER_H
