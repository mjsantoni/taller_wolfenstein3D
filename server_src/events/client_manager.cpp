#include "server/events/clients_manager.h"

ClientsManager::ClientsManager() {}

void ClientsManager::addNewPlayer(NetworkConnection socket, int id, SharedQueue<Event>& eventQueue, std::unordered_map<Coordinate, Positionable, Coordinate::HashFunction> map) {
    std::unique_lock<std::mutex> lock(m);
    Client* client = new Client(std::move(socket), eventQueue, id, map);
    clients.push_back(client);
    eventQueue.push(Event(CONNECT_PLAYER, id, INVALID));
}

void ClientsManager::notifyClients(Change& change) {
    std::unique_lock<std::mutex> lock(m);
    for (auto& client : clients) {
        client->update(change);
    }
}

void ClientsManager::killPlayers() {
    std::unique_lock<std::mutex> lock(m);
    for(auto& client : clients) {
        client->stop();
        delete client;
    }
}

ClientsManager::~ClientsManager() {}
