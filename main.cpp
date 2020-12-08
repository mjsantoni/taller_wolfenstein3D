#include <iostream>
#include <SDL.h>
#include "client/sdl_window.h"
#include "client/sdl_texture.h"
#include "client/sdl_exception.h"
#include "client/map.h"
#include "client/player.h"
#include "client/game.h"

/* App editor_src */
#include <QApplication>
#include "yaml-cpp/yaml.h"
#include "editor/editor.h"
#include <fstream>

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
    /* App editor_src */
    /*
    // Clase que contiene el loop principal
    QApplication app(argc, args);
    // Instancio el greeter
    Editor editor;
    editor.show();
    // Arranca el loop de la UI
    app.exec();*/

    return 0;
}
