#include "clientQT/config_checker.h"

int main(int argc, char* args[]) {
    QApplication app(argc, args);
    ConfigChecker checker;
    checker.show();
    app.exec();
    app.quit();
}
