#include "client/communication/server_listener.h"

#include <random>
#include <unistd.h>

#define MAX_CHANGES 100

ServerListener::~ServerListener() {
    //skt.closeSocket();
}

bool probability(float prob) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist10(0,100); // distribution in range [1, 10]
    return dist10(rng) < (prob * 100);
}


void ServerListener::run() {
    while (alive) {
        /* Es un simulador de eventos para testear */
        std::string msg;
        std::cout << "Server Listener listo para recibir\n";
        skt.recv_msg(msg);
        std::cout << "Se recibio el mensaje " << msg << std::endl;
        change_factory.createAndPushFromBytes(const_cast<char *>(msg.c_str()));
        //std::random_device dev;
        //std::mt19937 rng(dev());
        //std::uniform_int_distribution<std::mt19937::result_type> dist10(2,8);
        //Event event(dist10(rng),player_id,0);
        //std::cout << "Se creo un evento del player: " << player_id << " con ID: " << event.getEventID() <<" !!!\n";
    sleep(1);
    }
}

void ServerListener::stop() {
    alive = false;
    //socket.closeSocket();
}

ServerListener::ServerListener(NetworkConnection &_skt,
                               SharedQueue<Change>& _change_queue):
                               skt(_skt),
                               change_queue(_change_queue),
                               change_factory(change_queue),
                               alive(true){
}

