#ifndef TP_WOLFENSTEIN_CLIENTS_MANAGER_H
#define TP_WOLFENSTEIN_CLIENTS_MANAGER_H

#include <vector>
#include <mutex>
#include "server/game/client.h"
#include "common/change.h"
#include "common/event.h"
#include "common/shared_queue.h"

class ClientsManager {
private:
    std::vector<Client*> clients;
    std::mutex m;

public:
    ClientsManager() {}

    void addNewPlayer(NetworkConnection socket, int id, SharedQueue<Event>& eventQueue, std::map<Coordinate, Positionable> map) {
        std::unique_lock<std::mutex> lock(m);
        Client* client = new Client(std::move(socket), eventQueue, id, map);
        clients.push_back(client);
        eventQueue.push(Event(CONNECT_PLAYER, id, INVALID));
    }

    void notifyClients(Change& change) {
        std::unique_lock<std::mutex> lock(m);
        for (auto& client : clients) {
            client->update(change);
        }
    }
    void killPlayers() {
        std::unique_lock<std::mutex> lock(m);
        for(auto& client : clients) {
            client->stop();
            delete client;
        };
    }
};

#endif //TP_WOLFENSTEIN_CLIENTS_MANAGER_H
