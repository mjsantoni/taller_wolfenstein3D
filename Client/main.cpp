#include <iostream>
#include <SDL.h>
#include "Graphics/SdlWindow.h"
#include "Graphics/SdlTexture.h"
#include "Exceptions/SdlException.h"
#include "Game/Map.h"
#include "Game/Player.h"
#include "Game/Game.h"

/*
int main_2( int argc, char* args[] ) {
    try {
        SdlWindow window(800, 600);
        window.fill();
        SdlTexture image("tenor.gif", window);
        Area src_area(0, 0, 800, 600);
        Area dst_area(0, 0, 800, 600);
        image.render(src_area, dst_area);
        window.render();
        SDL_Delay(3000);
    }
    catch(SdlException& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
*/
int main( int argc, char* args[] ) {
    try {
        Game game(960, 600);
        game.start();
    }

    catch(SdlException& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
