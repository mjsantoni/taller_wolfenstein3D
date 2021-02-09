#include "server/events/client_handler.h"

#include <random>
#include <unistd.h>

ClientHandler::ClientHandler(NetworkConnection& _skt, SharedQueue<Event> &event_queue, int id) :
                             skt(_skt),
                             eventFactory(event_queue),
                             alive(true),
                             player_id(id) {
}

ClientHandler::~ClientHandler() {}

bool probability(float prob) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist10(0,100); // distribution in range [1, 10]
    return dist10(rng) < (prob * 100);
}


void ClientHandler::run() {
    std::cout << "[Client Handler] Starting.\n";
    while (alive) {
        //std::random_device dev;
        //std::mt19937 rng(dev());
        //std::uniform_int_distribution<std::mt19937::result_type> dist10(2,8);
        //Event event(dist10(rng),player_id,0);
        //std::cout << "Se creo un evento del player: " << player_id << " con ID: " << event.getEventID() <<" !!!\n";
        //eventFactory.pushNewEvent(event);

        //sleep(1);

        /* Es un simulador de eventos para testear */

        bool create_random_event = true;
        if (create_random_event) {
            std::string msg;
            //std::cout << "Voy a recibir\n";
            try {
                skt.recv_msg(msg);
            } catch (NetworkError& e) {
                break;
            }
            //std::cout << "recibi: " << msg << "\n";
            eventFactory.createAndPushFromBytes(const_cast<char *>(msg.c_str()));
            //std::random_device dev;
            //std::mt19937 rng(dev());
            //std::uniform_int_distribution<std::mt19937::result_type> dist10(2,8);
            //Event event(dist10(rng),player_id,0);
            //std::cout << "Se creo un evento del player: " << player_id << " con ID: " << event.getEventID() <<" !!!\n";

        }
    }
    std::cout << "[Client Handler] Stopping.\n";
}

void ClientHandler::stop() {
    alive = false;
}

int ClientHandler::getPlayerId() const {
    return player_id;
}
