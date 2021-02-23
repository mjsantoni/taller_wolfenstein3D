#ifndef TP_WOLFENSTEIN_DROP_HANDLER_H
#define TP_WOLFENSTEIN_DROP_HANDLER_H

#include "common/config_parser.h"
#include "server/game/map.h"
#include "server/game/drop.h"

class DropHandler {
 private:
  ConfigParser configParser;
  Map& map;

 public:
  DropHandler(const std::string& config_path, Map& _map);

  /* Procesa y aplica los drops generados por una muerte en el mapa. */
  void processDrops(const std::vector<Drop>& drops);

  ~DropHandler();
};

#endif //TP_WOLFENSTEIN_DROP_HANDLER_H
