#include <QFile>
#include "client/config_checker.h"

int main(int argc, char* args[]) {
    QApplication app(argc, args);
    ConfigChecker checker;
    QFile file("../client_src/client.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    app.setStyleSheet(styleSheet);
    checker.show();
    app.exec();
    app.quit();
}
