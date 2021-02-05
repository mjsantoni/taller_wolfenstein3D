#ifndef TP_WOLFENSTEIN_SERVER_HANDLER_H
#define TP_WOLFENSTEIN_SERVER_HANDLER_H

#include "common/thread.h"
#include "common/event_factory.h"
#include <atomic>

class ServerHandler : public Thread {
private:
    //NetworkConnection& skt;
    EventFactory eventFactory;
    std::atomic<bool> alive;
    int player_id;

public:
    explicit ServerHandler(SharedQueue<Event> &event_queue, int id);
    ~ServerHandler();

    void run() override;

    int getPlayerId() const;

    void stop();
};


#endif //TP_WOLFENSTEIN_SERVER_HANDLER_H
