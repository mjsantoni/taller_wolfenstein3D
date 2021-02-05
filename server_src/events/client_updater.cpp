#include "server/events/client_updater.h"
#include <unistd.h>

ClientUpdater::ClientUpdater(NetworkConnection& _sk, int id) :
                            skt(_sk),
                            change_queue(Change()),
                            player_id(id),
                            alive(true) {
    //std::cout << "CONSTRUCTOR DEL UPDATER" << skt.file_descriptor <<  " - PLAYER " << player_id << "\n";
}

ClientUpdater::~ClientUpdater() {}

void ClientUpdater::sendMap(std::map<Coordinate, Positionable> map) {
    for (auto& elem : map) {
        int x = elem.first.x;
        int y = elem.first.y;
        int id = elem.second.getId();
        Change change(MAP_INITIALIZER, id, x, y, false);
        skt.send_msg(change.serialize());

    }
}


void ClientUpdater::run() {
    while (alive) {
        Change change = change_queue.pop();
        if (change.isInvalid()) continue;
        if (change.isGlobal() || change.getPlayerID() == player_id) {
            //std::cout << "PLAYER " << player_id << " -> Popie un change de id: " << change.getChangeID() << "\n";
            //std::cout << "EN EL RUN DEL UPDATER " << skt.file_descriptor << " - PLAYER " << player_id << "\n";
            skt.send_msg(change.serialize());
        }
    }
}

void ClientUpdater::update(Change change) {change_queue.push(change);}


void ClientUpdater::stop() {
    alive = false;
    change_queue.close();
    //socket.closeSocket();
}

int ClientUpdater::getPlayerId() const {
    return player_id;
}
