//
// Created by andy on 10/12/20.
//

#include <client/game/client.h>

int main() {
    NetworkConnection socket("localhost", "8080");
    //Client client(socket);
    bool andygato = true;
    for (int i = 0; i < 11; i++) {
        std::string buffer;
        socket.recv_msg(buffer);
        std::cout << buffer << "\n";

    }
    socket.send_msg(Event(PLAYER_READY,0,0).serialize());
    socket.stopSending();

}

/*
int main() {
    NetworkConnection socket("localhost", "8080");
    Client client(socket);
    client.start();
}
*/