#include "server/game.h"
#include <cmath>

int main( int argc, char* args[] ) {
    Game game("../map.yaml");
    Player player("0");
    game.movePlayer(player, 0);
    game.movePlayer(player, 0);
    game.movePlayer(player, 0);
    game.movePlayer(player, 0);
    game.movePlayer(player, 0);
    game.movePlayer(player, 0);
    game.movePlayer(player, 0);
    game.movePlayer(player, M_PI/2);
    game.movePlayer(player, M_PI/2);
    game.movePlayer(player, M_PI/2);
    game.movePlayer(player, M_PI/2);
    game.movePlayer(player, M_PI/2);
    game.movePlayer(player, 3*M_PI/4);
    game.movePlayer(player, M_PI/2);

    return 0;
}
