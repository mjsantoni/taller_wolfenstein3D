//
// Created by andy on 30/1/21.
//

#include "client/event_updater.h"

EventUpdater::EventUpdater(NetworkConnection& _sk, int id) :
        skt(_sk),
        event_queue(Event()),
        player_id(id),
        alive(true) {
    std::cout << "CONSTRUCTOR DEL UPDATER" << skt.file_descriptor <<  " - PLAYER " << player_id << "\n";
}

EventUpdater::~EventUpdater() {}

void EventUpdater::run() {
    while (alive) {
        Event event = event_queue.pop();
        if (event.isInvalid()) continue;
        skt.sendMsg(event.serialize());
    }
}

void EventUpdater::update(Event event) {
    event_queue.push(event);
}


void EventUpdater::stop() {
    alive = false;
    event_queue.close();
    //socket.closeSocket();
}

int EventUpdater::getPlayerId() const {
    return player_id;
}
