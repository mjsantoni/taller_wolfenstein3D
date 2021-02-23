#ifndef TP_WOLFENSTEIN_COLISSION_HANDLER_H
#define TP_WOLFENSTEIN_COLISSION_HANDLER_H

#include "server/game/map.h"
#include "common/coordinate.h"

#define MOVE_SIZE 10
#define SAFE_DISTANCE 15

class ColissionHandler {
 private:
  Map& map;
  int move_size = MOVE_SIZE;
  int safe_distance = SAFE_DISTANCE;

 public:
  /* Clase principal de manejo de colisiones. */
  explicit ColissionHandler(Map& _map);

  /* Recibe una coordenada actual y el angulo y devuelve una nueva coordenada
   * a la que el player se moverá, contemplando colisiones con objetos. */
  Coordinate moveToPosition(const Coordinate& actual_pos, double angle);

  /* Obtiene los posicionables que se encuentran en el recorrido de movimiento
   * de una coordenada a otra de un player. */
  std::vector<std::pair<Coordinate, Positionable>>
  getCloseItems(const Coordinate& old_pos, const Coordinate& new_pos);

  /* Obtiene paredes o puertas cercanas a donde mire el player. */
  Coordinate getCloseBlocking(const Coordinate& pos, double angle, const std::string& category);
};

#endif //TP_WOLFENSTEIN_COLISSION_HANDLER_H
