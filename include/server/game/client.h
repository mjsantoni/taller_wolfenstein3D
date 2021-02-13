#ifndef TP_WOLFENSTEIN_CLIENT_H
#define TP_WOLFENSTEIN_CLIENT_H

#include "common/network_connection.h"
#include "server/events/client_handler.h"
#include "server/events/client_updater.h"
#include "common/shared_queue.h"
#include "common/event.h"
#include "common/map_item_identifiers.h"

class Client {
private:
    NetworkConnection sk;
    ClientHandler clientHandler;
    ClientUpdater clientUpdater;
public:
    Client(NetworkConnection _sk, SharedQueue<Event>& _sq, int id, std::unordered_map<Coordinate, Positionable, Coordinate::HashFunction> map) :
        sk(std::move(_sk)), clientHandler(sk, _sq,id), clientUpdater(sk,id, map) {
        clientHandler.start();
        clientUpdater.start();
    }

    void update(Change &change) { clientUpdater.update(change); }

    void stop() {
        sk.shutdownAll();
        clientHandler.stop();
        clientUpdater.stop();
        clientUpdater.join();
        clientHandler.join();
        sk.closeSocket();
    }
};

#endif //TP_WOLFENSTEIN_CLIENT_H
