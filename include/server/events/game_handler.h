#ifndef TP_WOLFENSTEIN_GAME_HANDLER_H
#define TP_WOLFENSTEIN_GAME_HANDLER_H

#include <atomic>
#include <string>
#include <vector>

#include "event_factory.h"
#include "server/game/game.h"
#include "event_processor.h"
#include "common/shared_queue.h"
#include "common/blocking_queue.h"
#include "common/change.h"
#include "server/events/client_handler.h"
#include "server/events/client_updater.h"
#include "common/network_connection.h"
#include "server/events/client.h"
#include "server/events/clients_manager.h"

class GameHandler : public Thread {
 private:
  SharedQueue<Event> eventQueue;
  BotsManager botsManager;
  Game game;
  ClientsManager clientsManager;
  EventProcessor eventProcessor;
  std::atomic<bool> alive;
  std::atomic<bool> can_join_player;
  std::mutex m;

  int min_players_in_lobby;
  int max_bots;
  int max_players;
  int id;
  std::string name;
  int game_duration;

 public:
  /* Constructor de la clase principal del flujo de una partida.
   * Recibe paths a config y mapa y parametros predefinidos por el menu de incio.*/
  GameHandler(const std::string& map_path, const std::string& config_path, int _min_players_in_lobby,
              int _max_players, int _max_bots, int _game_id, int _game_duration);

  /* Flujo principal del juego. Finaliza al concluir la partida o por
   * una llamada a stop. */
  void run() override;

  /* Agrega un nuevo player a la partida a traves del ClientsManager. Se mueve el socket
   * de la conexion. */
  void addNewPlayer(NetworkConnection fd);

  void stop();

  /* Notifica a todos los clientes de cambios. */
  void notifyClients(std::vector<Change>& changes);

  /* Metodo que espera hasta completar el lobby y luego empezar la partida. */
  void waitInLobby();

  void sendTops();

  void notifyTop(std::vector<std::pair<int, int>> top, int change_id);

  void addBots();

  bool canJoinPlayer();

  bool ended();

  /* Funcion final del juego que envia tops a los clientes. */
  void endGame();

  std::string getInformation();
};

#endif //TP_WOLFENSTEIN_GAME_HANDLER_H
