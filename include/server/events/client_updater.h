#ifndef TP_WOLFENSTEIN_CLIENT_UPDATER_H
#define TP_WOLFENSTEIN_CLIENT_UPDATER_H

#include "common/blocking_queue.h"
#include "common/change.h"
#include "common/network_connection.h"
#include "common/network_error.h"
#include "common/thread.h"
#include "common/coordinate.h"
#include "server/entities/positionable.h"
#include <atomic>
#include <queue>
#include <map>
#include <unordered_map>

class ClientUpdater : public Thread {
 private:
  NetworkConnection& skt;
  BlockingQueue<Change> change_queue;
  std::atomic<bool> alive;
  int player_id;
  std::unordered_map<Coordinate, Positionable, Coordinate::HashFunction> map;

 public:
  explicit ClientUpdater(NetworkConnection& _sk,
                         int i,
                         std::unordered_map<Coordinate, Positionable, Coordinate::HashFunction> map);
  ~ClientUpdater();

  void run() override;

  void stop();

  void update(Change change);

  int getPlayerId() const;

  void sendMap();
};

#endif //TP_WOLFENSTEIN_CLIENT_UPDATER_H
