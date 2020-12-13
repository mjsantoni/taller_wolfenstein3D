#include <QApplication>
#include "yaml-cpp/yaml.h"
#include "editor/editor.h"
#include <fstream>

int main( int argc, char* args[] ) {
    /* App editor_src */
    // Clase que contiene el loop principal
    QApplication app(argc, args);
    // Instancio el greeter
    Editor editor;
    editor.show();
    // Arranca el loop de la UI
    app.exec();

    return 0;
}

