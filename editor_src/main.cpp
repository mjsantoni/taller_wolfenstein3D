#include <QApplication>
#include "yaml-cpp/yaml.h"
#include "editor/editor.h"
#include <fstream>

int main( int argc, char* args[] ) {
    QApplication app(argc, args);
    QFile file("/home/agustin/Desktop/taller_wolfenstein3D/editor_src/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    app.setStyleSheet(styleSheet);
    Editor editor;
    editor.show();
    app.exec();

    return 0;
}

