#include <QFile>
#include "clientQT/config_checker.h"

int main(int argc, char* args[]) {
    QApplication app(argc, args);
    ConfigChecker checker;
    // QFile file("../ClientQT/client.qss");
    // file.open(QFile::ReadOnly);
    // QString styleSheet = QLatin1String(file.readAll());
    // app.setStyleSheet(styleSheet);
    checker.show();
    app.exec();
    app.quit();
}
