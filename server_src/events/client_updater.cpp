#include "server/events/client_updater.h"
#include <unistd.h>

ClientUpdater::ClientUpdater(int id) :
                             change_queue(Change()),
                             player_id(id),
                             alive(true) {
}

ClientUpdater::~ClientUpdater() {

}

void ClientUpdater::run() {
    while (alive) {
        Change change = change_queue.pop();
        std::cout << "PLAYER " << player_id << "Popie un change de id: " << change.getChangeID() << "\n";
        //if ((change.id == mi id && !isglobal) || isglobal) sendIntsBigEndian
        //else continue
        //Send changes.serialize()
        sleep(3);
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
