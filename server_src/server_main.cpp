#include "server/game.h"
#include <cmath>
#include <iostream>

int main( int argc, char* args[] ) {
    Game game("../map.yaml");
    Player player("0");
    Player player2("1");

    game.movePlayer(player2, M_PI/4);
    game.shoot(player,M_PI/4);

    //game.movePlayer(player, 0);
    //game.movePlayer(player, 0);
    //game.movePlayer(player, 0);
    //game.movePlayer(player, 0);
    //game.movePlayer(player, 0);
    //game.movePlayer(player, 0);
    //game.movePlayer(player, 0);
    //game.movePlayer(player, M_PI/2);
    //game.movePlayer(player, M_PI/2);
    //game.movePlayer(player, M_PI/2);
    //game.movePlayer(player, M_PI/2);
    //game.movePlayer(player, M_PI/2);
    //game.movePlayer(player, 3*M_PI/4);
    //game.movePlayer(player, M_PI/2);
    //game.show();
    return 0;
}
