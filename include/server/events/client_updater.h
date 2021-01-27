#ifndef TP_WOLFENSTEIN_CLIENT_UPDATER_H
#define TP_WOLFENSTEIN_CLIENT_UPDATER_H

#include "common/thread.h"
#include <atomic>
#include "common/change.h"
#include <queue>
#include "common/blocking_queue.h"
#include "common/network_connection.h"

class ClientUpdater : public Thread {
private:
    NetworkConnection& skt;
    BlockingQueue<Change> change_queue;
    std::atomic<bool> alive;
    int player_id;

public:
    explicit ClientUpdater(NetworkConnection& _sk, int i);
    ~ClientUpdater();

    void run() override;

    void stop();

    void update(Change change);

    int getPlayerId() const;
};


#endif //TP_WOLFENSTEIN_CLIENT_UPDATER_H
