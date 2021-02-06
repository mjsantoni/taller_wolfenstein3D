#ifndef TP_WOLFENSTEIN_CLIENT_UPDATER_H
#define TP_WOLFENSTEIN_CLIENT_UPDATER_H

#include "common/thread.h"
#include <atomic>
#include "common/change.h"
#include <queue>
#include "common/blocking_queue.h"
#include "common/network_connection.h"
#include "server/game/coordinate.h"
#include "server/game/positionable.h"
#include <map>

class ClientUpdater : public Thread {
private:
    NetworkConnection& skt;
    BlockingQueue<Change> change_queue;
    std::atomic<bool> alive;
    int player_id;
    std::map<Coordinate, Positionable> map;

public:
    explicit ClientUpdater(NetworkConnection& _sk, int i, std::map<Coordinate, Positionable> map);
    ~ClientUpdater();

    void run() override;

    void stop();

    void update(Change change);

    int getPlayerId() const;

    void sendMap();

};


#endif //TP_WOLFENSTEIN_CLIENT_UPDATER_H
