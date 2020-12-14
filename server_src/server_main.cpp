#include "server/server.h"
#include <cmath>

int main( int argc, char* args[] ) {
    Server server("../map.yaml");
    Player player("0");
    server.movePlayer(player, 0);
    server.movePlayer(player, 0);
    server.movePlayer(player, 0);
    server.movePlayer(player, 0);
    server.movePlayer(player, 0);
    server.movePlayer(player, 0);
    server.movePlayer(player, 0);
    server.movePlayer(player, M_PI/2);
    server.movePlayer(player, M_PI/2);
    server.movePlayer(player, M_PI/2);
    server.movePlayer(player, M_PI/2);
    server.movePlayer(player, M_PI/2);
    server.movePlayer(player, 3*M_PI/4);
    server.movePlayer(player, M_PI/2);

    return 0;
}
