#ifndef TP_WOLFENSTEIN_CLIENTS_MANAGER_H
#define TP_WOLFENSTEIN_CLIENTS_MANAGER_H

#include <vector>
#include <mutex>
#include "server/events/client.h"
#include "common/change.h"
#include "common/event.h"
#include "common/shared_queue.h"

class ClientsManager {
 private:
  std::vector<Client*> clients;
  std::mutex m;

 public:

  /* Constructor de la clase contenedora de clientes. */
  ClientsManager();

  /* Añade un nuevo Client creandolo con el socket y su cola de eventos. */
  void addNewPlayer(NetworkConnection socket, int id,
                    SharedQueue<Event>& eventQueue,
                    std::unordered_map<Coordinate,
                                       Positionable, Coordinate::HashFunction> map);

  /* Notifica a todos los clientes del cambio recibido por parametro. */
  void notifyClients(Change& change);

  /* Destructor de los clientes. */
  void killPlayers();

  ~ClientsManager();
};

#endif //TP_WOLFENSTEIN_CLIENTS_MANAGER_H
