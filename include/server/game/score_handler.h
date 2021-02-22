#ifndef TP_WOLFENSTEIN_SCORE_HANDLER_H
#define TP_WOLFENSTEIN_SCORE_HANDLER_H

#include <map>
#include <vector>
#include <unordered_map>

class ScoreHandler {
 private:
  std::unordered_map<int, int> kills;
  std::unordered_map<int, int> bulletsShot;
  std::unordered_map<int, int> treasurePoints;

  std::vector<std::pair<int, int>> getTop(const std::unordered_map<int, int>& map, int n);

 public:

  ScoreHandler() = default;

  /* Agrega n kills al jugador con el id */
  void addKill(int id, int n);

  /* Agrega n balas disparadas al jugador con el id */
  void addBulletsShot(int id, int n);

  /* Agrega n puntos al jugador con el id */
  void addTreasurePoints(int id, int n);

  /* Devuelve un vector de los N mejores asesinos. El vector esta separado en id/asesinatos. */
  std::vector<std::pair<int, int>> getTopFraggers(int n);
  /* Devuelve un vector de los N mas gastadores. El vector esta separado en id/balas_usadas. */
  std::vector<std::pair<int, int>> getTopShooters(int n);
  /* Devuelve un vector de los N mejores puntajes. El vector esta separado en id/puntaje. */
  std::vector<std::pair<int, int>> getTopCollectors(int n);
};

#endif //TP_WOLFENSTEIN_SCORE_HANDLER_H
