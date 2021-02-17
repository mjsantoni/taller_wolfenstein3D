//
// Created by andy on 10/12/20.
//

#include <client/game/client.h>

int main() {
    NetworkConnection socket("localhost", "8080");
    Client client(socket);
    client.startGame();
}
