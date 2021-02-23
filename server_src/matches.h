#ifndef TP_WOLFENSTEIN_SERVER_SRC_MATCHES_H_
#define TP_WOLFENSTEIN_SERVER_SRC_MATCHES_H_

#include <algorithm>
#include <mutex>
#include <vector>
#include "server/events/game_handler.h"
#include "common/network_connection.h"

#define CREATE_GAME "0"
#define JOIN_GAME "1"
#define SUCCESS "2"
#define ERROR "3"
#define BACK "4"


class Matches {
 private:
  std::mutex m;
  std::vector<GameHandler*> matches;

 public:
  void addNewMatch(GameHandler* match) {
    std::unique_lock<std::mutex> lock(m);
    matches.push_back(match);
  }

  int getSize() {
    std::unique_lock<std::mutex> lock(m);
    return matches.size();
  }

  bool canJoinPlayer(int id) {
    std::unique_lock<std::mutex> lock(m);
    return matches[id]->canJoinPlayer();
  }

  void addNewPlayer(int id, NetworkConnection skt) {
    std::unique_lock<std::mutex> lock(m);
    matches[id]->addNewPlayer(std::move(skt));
  }

  void sendGames(NetworkConnection& skt) {
    std::unique_lock<std::mutex> lock(m);
    for (auto& game : matches) {
      if (game->canJoinPlayer()) {
        skt.send_msg(game->getInformation());
      }
    }
    skt.send_msg(SUCCESS);
  }

  static bool is_null(GameHandler* gh) { return !gh; }

  void killDead() {
    std::unique_lock<std::mutex> lock(m);
    int i = 0;
    for (auto& game : matches) {
      if (game->ended()) {
        game->join();
        delete game;
        matches[i] = nullptr;
      }
      i++;
    }
    matches.erase(std::remove_if(matches.begin(), matches.end(), is_null),
                  matches.end());
  }

  void stopGames() {
    std::unique_lock<std::mutex> lock(m);
    for (auto& th_game : matches) {
      th_game->stop();
      th_game->join();
      delete th_game;
    }
  }

};

#endif //TP_WOLFENSTEIN_SERVER_SRC_MATCHES_H_
