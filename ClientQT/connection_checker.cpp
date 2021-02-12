#include "clientQT/connection_checker.h"
#include "ui_connect.h"

ConnectionChecker::ConnectionChecker(QMainWindow *parent) : QMainWindow(parent) {
    Ui::ConnectionChecker checker;
    checker.setupUi(this);
    connectEvents();
    QLineEdit* hostLine = findChild<QLineEdit*>("hostLine");
    QLineEdit* portLine = findChild<QLineEdit*>("portLine");
}


QString ConnectionChecker::getHost() {
    QLineEdit* hostLine = findChild<QLineEdit*>("hostLine");
    // return atoi(hostLine->text().toStdString().c_str());
    return hostLine->text();
}

QString ConnectionChecker::getPort() {
    QLineEdit* portLine = findChild<QLineEdit*>("portLine");
    //return atoi(portLine->text().toStdString().c_str());
    return portLine->text();
}

void ConnectionChecker::connectEvents(){
     QCommandLinkButton* button = findChild<QCommandLinkButton*>("connectButton");
     connect(button, &QCommandLinkButton::clicked,this, &ConnectionChecker::showConnections);

}

void ConnectionChecker::showConnections(){
    QLabel* hostLabel = findChild<QLabel*>("hostLabel");
    QLabel*  portLabel = findChild<QLabel*>("portLabel");
    hostLabel->setText(getHost());
    portLabel->setText(getPort());
}