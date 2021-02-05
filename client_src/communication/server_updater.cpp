//
// Created by andy on 30/1/21.
//

#include "client/communication/server_updater.h"

ServerUpdater::ServerUpdater(NetworkConnection& _sk, int id) :
        skt(_sk),
        event_queue(Event()),
        player_id(id),
        alive(true) {
}

ServerUpdater::~ServerUpdater() {}

void ServerUpdater::run() {
    while (alive) {
        Event event = event_queue.pop();
        if (event.isInvalid()) continue;
        skt.send_msg(event.serialize());
        std::cout << "El evento " << event.getEventID() << " se envio al socket\n";
    }
}

void ServerUpdater::update(Event event) {
    std::cout << "Se envia a la cola de eventos el evento "<< event.getEventID() << " del jugador " << event.getPlayerID() << " con valor " << event.getValue()  << std::endl;
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
