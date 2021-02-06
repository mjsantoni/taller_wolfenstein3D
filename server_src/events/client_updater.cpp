#include "server/events/client_updater.h"
#include <unistd.h>

ClientUpdater::ClientUpdater(NetworkConnection& _sk, int id, std::map<Coordinate, Positionable> _map) :
                            skt(_sk),
                            change_queue(Change()),
                            player_id(id),
                            alive(true),
                            map(_map) {
    //std::cout << "CONSTRUCTOR DEL UPDATER" << skt.file_descriptor <<  " - PLAYER " << player_id << "\n";
}

ClientUpdater::~ClientUpdater() {}

void ClientUpdater::sendMap() {
    for (auto& elem : map) {
        int x = elem.first.x;
        int y = elem.first.y;
        int id = elem.second.getId();
        Change change(MAP_INITIALIZER, id, x, y, false);
        skt.send_msg(change.serialize());

    }
}

void ClientUpdater::run() {
    sendMap();
    while (alive) {
        Change change = change_queue.pop();
        if (change.isInvalid()) continue;
        if (change.isGlobal() || change.getPlayerID() == player_id) {
            //std::cout << "PLAYER " << player_id << " -> Popie un change de id: " << change.getChangeID() << "\n";
            //std::cout << "EN EL RUN DEL UPDATER " << skt.file_descriptor << " - PLAYER " << player_id << "\n";
            skt.send_msg(change.serialize());
            std::cout << "Server envia el mensaje " << change.serialize() << std::endl;
        }
    }
    std::cout << "Termino el ClientUpdater\n";
}

void ClientUpdater::update(Change change) {change_queue.push(change);}


void ClientUpdater::stop() {
    alive = false;
    change_queue.close();
}

int ClientUpdater::getPlayerId() const {
    return player_id;
}
