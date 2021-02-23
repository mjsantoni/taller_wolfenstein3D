#ifndef TP_WOLFENSTEIN_CLIENT_HANDLER_H
#define TP_WOLFENSTEIN_CLIENT_HANDLER_H

#include "common/thread.h"
#include "server/events/event_factory.h"
#include "common/network_connection.h"
#include "common/network_error.h"
#include <atomic>

class ClientHandler : public Thread {
 private:
  NetworkConnection& skt;
  EventFactory eventFactory;
  std::atomic<bool> alive;
  int player_id;

 public:
  /* Constructor de la clase que se ocupa de recibir eventos, desserializarlos
   * y enviarlos a la cola de eventos. Recibe una referencia al socket que utiliza. */
  explicit ClientHandler(NetworkConnection& _skt, SharedQueue<Event>& event_queue, int id);

  ~ClientHandler();

  void run() override;

  int getPlayerId() const;

  void stop();
};

#endif //TP_WOLFENSTEIN_CLIENT_HANDLER_H
