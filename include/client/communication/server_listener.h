#ifndef TP_WOLFENSTEIN_SERVER_LISTENER_H
#define TP_WOLFENSTEIN_SERVER_LISTENER_H

#include "common/thread.h"
#include "server/events/event_factory.h"
#include "change_factory.h"
#include <atomic>
#include <common/change.h>
#include <common/network_connection.h>
#include <common/network_error.h>

class ServerListener : public Thread {
private:
    NetworkConnection& skt;
    SharedQueue<Change>& change_queue;
    ChangeFactory change_factory;
    std::atomic<bool> alive;

public:
    ServerListener(NetworkConnection &_skt, SharedQueue<Change>& _change_queue);
    ServerListener();
    ~ServerListener();

    void run() override;

    int getPlayerId() const;

    void stop();
};


#endif //TP_WOLFENSTEIN_SERVER_LISTENER_H
