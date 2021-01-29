#include "server/events/client_handler.h"

#include <random>
#include <unistd.h>

ClientHandler::ClientHandler(SharedQueue<Event> &event_queue, int id) :
                             eventFactory(event_queue),
                             alive(true),
                             player_id(id) {

}

ClientHandler::~ClientHandler() {
    //skt.closeSocket();
}

bool probability(float prob) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist10(0,100); // distribution in range [1, 10]
    return dist10(rng) < (prob * 100);
}


void ClientHandler::run() {
    while (alive) {
        /* Es un simulador de eventos para testear */
        bool create_random_event = probability(0.5);
        if (create_random_event) {
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist10(2,8);
            Event event(dist10(rng),player_id,0);
            std::cout << "Se creo un evento del player: " << player_id << " con ID: " << event.getEventID() <<" !!!\n";
            eventFactory.pushNewEvent(event);
        }
        sleep(1);

    }

}

void ClientHandler::stop() {
    alive = false;
    //socket.closeSocket();
}

int ClientHandler::getPlayerId() const {
    return player_id;
}
