//
// Created by andy on 10/12/20.
//

#include <client/game/client.h>

NetworkConnection connectToServer() {
    return NetworkConnection("localhost", "8080");
}
/*
int main() {
    NetworkConnection socket = connectToServer();
    Client client(socket);
    client.startGame();
}
*/