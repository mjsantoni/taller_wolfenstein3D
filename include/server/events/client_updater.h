#ifndef TP_WOLFENSTEIN_CLIENT_UPDATER_H
#define TP_WOLFENSTEIN_CLIENT_UPDATER_H

#include "common/thread.h"
#include <atomic>
#include "common/change.h"
#include <queue>

class ClientUpdater : public Thread {
private:
    //NetworkConnection& skt;
    std::atomic<bool> alive;
    int player_id;
    std::queue<Change> changes;

public:
    explicit ClientUpdater();
    ~ClientUpdater();

    void run() override;

    void stop();

    void update(Change change);

    int getPlayerId() const;
};


#endif //TP_WOLFENSTEIN_CLIENT_UPDATER_H
