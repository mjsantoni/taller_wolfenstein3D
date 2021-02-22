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
  Client(NetworkConnection _sk, SharedQueue<Event>& _sq, int id,
         std::unordered_map<Coordinate,
                            Positionable, Coordinate::HashFunction> map);

  void update(Change& change);

  void stop();
};

#endif //TP_WOLFENSTEIN_CLIENT_H
