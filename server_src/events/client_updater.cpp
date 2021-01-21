#include "server/events/client_updater.h"

ClientUpdater::ClientUpdater() {

}

ClientUpdater::~ClientUpdater() {

}

void ClientUpdater::run() {
    while (alive) {
        if (changes.empty()) continue;
        //Send changes.serialize()
    }

}

void ClientUpdater::update(Change change) {
    changes.push(change);
}

void ClientUpdater::stop() {
    /*
    alive = false;
    socket.closeSocket();
    */

}

int ClientUpdater::getPlayerId() const {
    return player_id;
}
