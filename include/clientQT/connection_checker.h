#ifndef TP_WOLFENSTEIN_CONNECTION_CHECKER_H
#define TP_WOLFENSTEIN_CONNECTION_CHECKER_H

#include <QMainWindow>

class ConnectionChecker: public QMainWindow {
public:
    explicit ConnectionChecker(QMainWindow *parent = 0);
    QString getHost();
    QString getPort();
    void connectEvents();
    void showConnections();
};

#endif //TP_WOLFENSTEIN_CONNECTION_CHECKER_H
