#include "server/events/client_updater.h"

ClientUpdater::ClientUpdater(BlockingQueue<Change>& _change_queue, int id) :
                             change_queue(_change_queue),
                             player_id(id),
                             alive(true) {
}

ClientUpdater::~ClientUpdater() {

}

void ClientUpdater::run() {
    while (alive) {
        //Change change = change_queue.pop();
        //if ((change.id == mi id && !isglobal) || isglobal) sendIntsBigEndian
        //else continue
        //Send changes.serialize()
    }

}

void ClientUpdater::update(Change change) {
    change_queue.push(change);
}

void ClientUpdater::stop() {
    alive = false;
    //socket.closeSocket();
}

int ClientUpdater::getPlayerId() const {
    return player_id;
}
