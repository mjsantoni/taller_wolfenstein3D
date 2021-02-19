#include "server/events/client.h"

Client::Client(NetworkConnection _sk, SharedQueue<Event>& _sq, int id,
               std::unordered_map<Coordinate,
               Positionable, Coordinate::HashFunction> map) :
               sk(std::move(_sk)), clientHandler(sk, _sq,id), clientUpdater(sk,id, map) {
    clientHandler.start();
    clientUpdater.start();
}

void Client::update(Change &change) { clientUpdater.update(change); }

void Client::stop() {
    sk.shutdownAll();
    clientHandler.stop();
    clientUpdater.stop();
    clientUpdater.join();
    clientHandler.join();
    sk.closeSocket();
}