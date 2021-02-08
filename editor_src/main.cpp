#include <QApplication>
#include "yaml-cpp/yaml.h"
#include "editor/editor.h"
#include <fstream>
#include <QDebug>
#include <QStyle>
#include <QStyleFactory>

int main( int argc, char* args[] ) {
    QApplication app(argc, args);
    QStyle *style = QStyleFactory::create("windows");
    if(style)
    {
        qDebug("windows loaded!");
        QApplication::setStyle(style);
    }
    QFile file("/home/agustin/Desktop/taller_wolfenstein3D/editor_src/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    app.setStyleSheet(styleSheet);
    Editor editor;
    editor.show();
    app.exec();

    return 0;
}

