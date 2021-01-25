#include "server/events/client_handler.h"

ClientHandler::ClientHandler(SharedQueue<Event> &event_queue, int id) :
                             eventFactory(event_queue),
                             alive(true),
                             player_id(id) {

}

ClientHandler::~ClientHandler() {
    //skt.closeSocket();
}

void ClientHandler::run() {
    /*
    while (connection is not closed) {
        std::vector<uint8_t> bytes_recv = skt.recv();
        eventFactory.createAndPushFromBytes(bytes_recv);
    }
    */
}

void ClientHandler::stop() {
    /*
    alive = false;
    socket.closeSocket();
    */
}

int ClientHandler::getPlayerId() const {
    return player_id;
}
