//
// Created by andy on 30/1/21.
//

#ifndef TP_WOLFENSTEIN_SERVER_UPDATER_H
#define TP_WOLFENSTEIN_SERVER_UPDATER_H

#include <common/network_connection.h>
#include <common/event.h>
#include <atomic>
#include <common/blocking_queue.h>
#include <common/thread.h>

class ServerUpdater : public Thread {
private:
    NetworkConnection& skt;
    BlockingQueue<Event>& event_queue;
    std::atomic<bool> alive;

public:
    explicit ServerUpdater(NetworkConnection& _sk,
                           BlockingQueue<Event>& _event_queue);
    ~ServerUpdater();
    void run() override;
    void stop();
    void update(Event event);

};


#endif //TP_WOLFENSTEIN_SERVER_UPDATER_H
