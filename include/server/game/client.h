#ifndef TP_WOLFENSTEIN_CLIENT_H
#define TP_WOLFENSTEIN_CLIENT_H

#include "common/network_connection.h"
#include "server/events/client_handler.h"
#include "server/events/client_updater.h"
#include "common/shared_queue.h"
#include "common/event.h"

class Client {
private:
    NetworkConnection sk;
    ClientHandler clientHandler;
    ClientUpdater clientUpdater;
public:
    Client(NetworkConnection _sk, SharedQueue<Event>& _sq, int id) : sk(std::move(_sk)), clientHandler(_sq,id), clientUpdater(sk,id) {
        clientHandler.start();
        clientUpdater.start();
    }

    void update(Change &change) { clientUpdater.update(change); }

    void stop() {
        clientUpdater.stop();
        clientUpdater.join();

        clientHandler.stop();
        clientHandler.join();
        sk.closeSocket();
    }
};

#endif //TP_WOLFENSTEIN_CLIENT_H
