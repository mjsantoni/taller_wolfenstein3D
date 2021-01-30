//
// Created by andy on 30/1/21.
//

#ifndef TP_WOLFENSTEIN_EVENT_UPDATER_H
#define TP_WOLFENSTEIN_EVENT_UPDATER_H

#include <common/network_connection.h>
#include <common/event.h>
#include <atomic>
#include <common/blocking_queue.h>
#include <common/thread.h>

class EventUpdater : public Thread {
private:
    NetworkConnection& skt;
    BlockingQueue<Event> event_queue;
    std::atomic<bool> alive;
    int player_id;

public:
    explicit EventUpdater(NetworkConnection& _sk, int i);
    ~EventUpdater();
    void run() override;
    void stop();
    void update(Event event);
    int getPlayerId() const;

};


#endif //TP_WOLFENSTEIN_EVENT_UPDATER_H
