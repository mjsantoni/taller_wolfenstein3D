#ifndef TP_WOLFENSTEIN_SERVER_SRC_SERVER_ACCEPTOR_H_
#define TP_WOLFENSTEIN_SERVER_SRC_SERVER_ACCEPTOR_H_

#include <vector>
#include <atomic>
#include "server/events/game_handler.h"
#include "common/network_acceptor.h"
#include "common/network_error.h"
#include "common/network_connection.h"
#include "common/thread.h"
#include "server/matches.h"
#include "server_routes.h"
#include "server/menu_events.h"

class ServerMenuHandler : public Thread{
  NetworkConnection socket;
  Matches& matches;

 public:
  ServerMenuHandler(NetworkConnection _socket, Matches& _matches);

  void run() override;

  int createGame(NetworkConnection& skt, std::string& options);

  bool joinGame(int game_id, NetworkConnection socket);

  std::vector<int> split(const std::string& bytes);

  void stop();
};

#endif //TP_WOLFENSTEIN_SERVER_SRC_SERVER_ACCEPTOR_H_
