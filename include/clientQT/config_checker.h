#ifndef TP_WOLFENSTEIN_CONFIG_CHECKER_H
#define TP_WOLFENSTEIN_CONFIG_CHECKER_H

#include <iostream>
#include <QMainWindow>
#include <QApplication>
#include <common/network_connection.h>
#include <common/network_error.h>

class ConfigChecker: public QMainWindow {
    NetworkConnection sk;
    bool server_found = false;
    bool options_send = false;
public:

    explicit ConfigChecker(QMainWindow *parent = 0);
    std::string getHost();
    std::string getPort();
    void connectEvents();
    void showConnections();
    void lookForServer();
    void chooseActions();
    void createNewGame();
    void joinGame();
    void showConnectionError();

    void showLobby();
};

#endif //TP_WOLFENSTEIN_CONNECTION_CHECKER_H
