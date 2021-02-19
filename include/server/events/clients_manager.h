#ifndef TP_WOLFENSTEIN_CLIENTS_MANAGER_H
#define TP_WOLFENSTEIN_CLIENTS_MANAGER_H

#include <vector>
#include <mutex>
#include "server/events/client.h"
#include "common/change.h"
#include "common/event.h"
#include "common/shared_queue.h"

class ClientsManager {
private:
    std::vector<Client*> clients;
    std::mutex m;

public:
    ClientsManager();

    void addNewPlayer(NetworkConnection socket, int id,
                      SharedQueue<Event>& eventQueue,
                      std::unordered_map<Coordinate,
                      Positionable, Coordinate::HashFunction> map);

    void notifyClients(Change& change);

    void killPlayers();

    ~ClientsManager();
};

#endif //TP_WOLFENSTEIN_CLIENTS_MANAGER_H
