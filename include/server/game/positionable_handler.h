#ifndef TP_WOLFENSTEIN_POSITIONABLEHANDLER_H
#define TP_WOLFENSTEIN_POSITIONABLEHANDLER_H

#include "server/entities/positionable.h"
#include "common/config_parser.h"

class PositionableHandler {

 public:
  /* Clase que genera los posicionables a poner en el mapa. */
  PositionableHandler();

  Positionable createBlockingItem(const std::string& type, int id);
  Positionable createItem(const std::string& type, int id);

  ~PositionableHandler() {}
};

#endif //TP_WOLFENSTEIN_POSITIONABLEHANDLER_H
