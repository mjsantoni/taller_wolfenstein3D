#include <iostream>
#include <SDL.h>
#include "client/SdlWindow.h"
#include "client/SdlTexture.h"
#include "client/SdlException.h"
#include "client/Map.h"
#include "client/Player.h"
#include "client/Game.h"

/* App editor */
#include <QApplication>
#include "yaml-cpp/yaml.h"
#include "editor/Editor.h"
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

    /* App editor *//*
    // Clase que contiene el loop principal
    QApplication app(argc, args);
    // Instancio el greeter
    Editor editor;
    editor.show();
    // Arranca el loop de la UI
    app.exec();*/

    return 0;
}
