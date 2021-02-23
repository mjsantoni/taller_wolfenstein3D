#ifndef TP_WOLFENSTEIN_SERVER_SRC_MATCHES_H_
#define TP_WOLFENSTEIN_SERVER_SRC_MATCHES_H_

#include <algorithm>
#include <mutex>
#include <vector>
#include "server/events/game_handler.h"
#include "common/network_connection.h"
#include "server/menu_events.h"

class Matches {
 private:
  std::mutex m;
  std::vector<GameHandler*> matches;

 public:
    Matches();
    ~Matches();

  void addNewMatch(GameHandler* match);

  int getSize();

  bool canJoinPlayer(int id);

  void addNewPlayer(int id, NetworkConnection skt);

  void sendGames(NetworkConnection& skt);

  void killDead();

  void stopGames();
};

#endif //TP_WOLFENSTEIN_SERVER_SRC_MATCHES_H_
