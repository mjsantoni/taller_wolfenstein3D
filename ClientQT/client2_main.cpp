#include "clientQT/client2.h"

int main(int argc, char* args[]) {
    Client2 pepe;
    QApplication app(argc, args);
    ConnectionChecker checker;
    checker.show();
    app.exec();
    pepe.lookForServer();
    pepe.chooseActions();
    //pepe.createNewGame();
    //pepe.joinGame();
}
