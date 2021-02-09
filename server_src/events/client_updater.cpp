#include "server/events/client_updater.h"
#include <unistd.h>

ClientUpdater::ClientUpdater(NetworkConnection& _sk, int id, std::map<Coordinate, Positionable> _map) :
                            skt(_sk),
                            change_queue(Change()),
                            player_id(id),
                            alive(true),
                            map(_map) {
}

ClientUpdater::~ClientUpdater() {}

void ClientUpdater::sendMap() {
    std::cout << "[Client Updater] Sending map.\n";
    for (auto& elem : map) {
        int x = elem.first.x;
        int y = elem.first.y;
        int id = elem.second.getId();
        Change change(MAP_INITIALIZER, id, x, y, false);
        skt.send_msg(change.serialize());
    }
}

void ClientUpdater::run() {
    std::cout << "[Client Updater] Starting.\n";
    sendMap();
    while (alive) {
        Change change = change_queue.pop();
        if (change.isInvalid()) continue;
        if (change.isGlobal() || change.getPlayerID() == player_id) {
            skt.send_msg(change.serialize());
            std::cout << "Server sends " << change.serialize() << std::endl;
        }
    }
    std::cout << "[Client Updater] Stopping.\n";
}

void ClientUpdater::update(Change change) { change_queue.push(change); }


void ClientUpdater::stop() {
    alive = false;
    change_queue.close();
}

int ClientUpdater::getPlayerId() const {
    return player_id;
}
