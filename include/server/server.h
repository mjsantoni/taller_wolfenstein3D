#ifndef TP_WOLFENSTEIN_SERVER_H
#define TP_WOLFENSTEIN_SERVER_H

#include <vector>
#include <atomic>
#include "server/events/game_handler.h"
#include "common/network_acceptor.h"
#include "common/network_error.h"
#include "common/network_connection.h"
#include "common/thread.h"
#include "server/server_menu_handler.h"
#include "server/matches.h"

class Server : public Thread {
 private:

  Matches matches;
  std::vector<ServerMenuHandler*> handlers;
  NetworkAcceptor networkAcceptor;
  std::atomic<bool> accepting_connections;

 public:
  Server(NetworkAcceptor socket);
  ~Server() override;

  void run() override;

  void stop();

  void closeHandlers();
};

#endif //TP_WOLFENSTEIN_SERVER_H
