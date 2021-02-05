//
// Created by andy on 30/1/21.
//

#include "client/communication/server_updater.h"

ServerUpdater::ServerUpdater(NetworkConnection& _sk, int id) :
        skt(_sk),
        event_queue(Event()),
        player_id(id),
        alive(true) {
    std::cout << "CONSTRUCTOR DEL UPDATER" << skt.file_descriptor <<  " - PLAYER " << player_id << "\n";
}

ServerUpdater::~ServerUpdater() {}

void ServerUpdater::run() {
    while (alive) {
        Event event = event_queue.pop();
        if (event.isInvalid()) continue;
        skt.sendMsg(event.serialize());
    }
}

void ServerUpdater::update(Event event) {
    event_queue.push(event);
}


void ServerUpdater::stop() {
    alive = false;
    event_queue.close();
    //socket.closeSocket();
}

int ServerUpdater::getPlayerId() const {
    return player_id;
}
