#ifndef TP_WOLFENSTEIN_SERVER_H
#define TP_WOLFENSTEIN_SERVER_H

#include <vector>
#include <atomic>
#include "server/events/game_handler.h"
#include "common/network_acceptor.h"
#include "common/network_error.h"
#include "common/network_connection.h"
#include "common/thread.h"

class Server : public Thread {
 private:
  std::vector<GameHandler*> matches;
  NetworkAcceptor networkAcceptor;
  std::atomic<bool> accepting_connections;

 public:
  Server(NetworkAcceptor socket);
  ~Server() override;

  void run() override;

  void stop();

  bool joinGame(int game_id, NetworkConnection socket);

  int createGame(NetworkConnection& skt, std::string& options);

  void killDead();

  void stopGames();

  std::vector<int> split(const std::string& bytes);

  void sendGames(NetworkConnection& socket);
};

#endif //TP_WOLFENSTEIN_SERVER_H
