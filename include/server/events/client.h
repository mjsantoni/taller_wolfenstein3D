#ifndef TP_WOLFENSTEIN_CLIENT_H
#define TP_WOLFENSTEIN_CLIENT_H

#include "common/network_connection.h"
#include "server/events/client_handler.h"
#include "server/events/client_updater.h"
#include "common/shared_queue.h"
#include "common/event.h"

class Client {
 private:
  NetworkConnection sk;
  ClientHandler clientHandler;
  ClientUpdater clientUpdater;

 public:
  /* Constructor de la clase que almacena toda la comunicacion con el cliente.
   */
  Client(NetworkConnection _sk, SharedQueue<Event>& _sq, int id,
         std::unordered_map<Coordinate,
                            Positionable, Coordinate::HashFunction> map);

  /* Envia cambios al ClientUpdater para su posterior envio por socket,
   * libera al ClientUpdater de su bloqueo por cv. */
  void update(Change& change);

  void stop();
};

#endif //TP_WOLFENSTEIN_CLIENT_H
