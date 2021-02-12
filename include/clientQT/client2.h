//
// Created by francisco on 11/2/21.
//

#ifndef TP_WOLFENSTEIN_CLIENT2_H
#define TP_WOLFENSTEIN_CLIENT2_H

#include "common/network_connection.h"
#include "connection_checker.h"
#include "common/network_error.h"
#include <QLineEdit>
#include <QApplication>
#include <iostream>


class Client2 {
    NetworkConnection sk;
    bool server_found = false;
    bool options_send = false;
public:
    Client2();

    void lookForServer();

    void chooseActions();

    void createNewGame();

    void joinGame();


};


#endif //TP_WOLFENSTEIN_CLIENT2_H
