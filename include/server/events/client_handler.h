#ifndef TP_WOLFENSTEIN_CLIENT_HANDLER_H
#define TP_WOLFENSTEIN_CLIENT_HANDLER_H

#include "common/thread.h"
#include "common/event_factory.h"
#include <atomic>

class ClientHandler : public Thread {
private:
    //NetworkConnection& skt;
    EventFactory eventFactory;
    std::atomic<bool> alive;
    int player_id;

public:
    explicit ClientHandler(SharedQueue<Event> &event_queue);
    ~ClientHandler();

    void run() override;

    int getPlayerId() const;

    void stop();
};


#endif //TP_WOLFENSTEIN_CLIENT_HANDLER_H
