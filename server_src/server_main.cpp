#include "server/game.h"
#include <cmath>
#include <iostream>

int main( int argc, char* args[] ) {
    Game game("../map.yaml");
    Player player("0");
    game.movePlayer(player, 0);
    std::cout << "Muevo player\n";
    game.movePlayer(player, 0);
    std::cout << "Muevo player\n";
    game.movePlayer(player, 0);
    std::cout << "Muevo player\n";
    game.movePlayer(player, 0);
    std::cout << "Muevo player\n";
    game.movePlayer(player, 0);
    std::cout << "Muevo player\n";
    game.movePlayer(player, 0);
    std::cout << "Muevo player\n";
    game.movePlayer(player, 0);
    std::cout << "Muevo player\n";
    game.movePlayer(player, M_PI/2);
    std::cout << "Muevo player\n";
    game.movePlayer(player, M_PI/2);
    std::cout << "Muevo player\n";
    game.movePlayer(player, M_PI/2);
    std::cout << "Muevo player\n";
    game.movePlayer(player, M_PI/2);
    std::cout << "Muevo player5\n";
    game.movePlayer(player, M_PI/2);
    std::cout << "Muevo player\n";
    game.movePlayer(player, 3*M_PI/4);
    std::cout << "Muevo player\n";
    game.movePlayer(player, M_PI/2);
    game.show();
    return 0;
}
