#include "clientQT/config_checker.h"

int main(int argc, char* args[]) {
    QApplication app(argc, args);
    ConfigChecker checker;
    checker.show();
    app.exec();
    //checker.lookForServer();
    app.quit();
    //checker.chooseActions();
    //pepe.createNewGame();
    //pepe.joinGame();
}
