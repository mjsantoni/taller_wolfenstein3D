#include "clientQT/config_checker.h"
#include "ui_connect.h"


ConfigChecker::ConfigChecker(QMainWindow *parent) : QMainWindow(parent), sk(-1) {
    Ui::ConfigChecker checker;
    checker.setupUi(this);
    QWidget *error_widget = findChild<QWidget*>("errorWidget");
    error_widget->hide();
    connectEvents();
}

void ConfigChecker::lookForServer() {
    try {
        NetworkConnection connection(getHost().c_str(), getPort().c_str());
        sk = std::move(connection);
        std::cout << "Conexion establecida correctamente\n";
        server_found = true;
        showLobby();
    } catch (const NetworkError& e) {
        showConnectionError();
    }
}

void ConfigChecker::chooseActions() {
    while (true) {
        std::string data;
        std::cout << "Ingrese modo: 0 -> Create / 1 -> Join: ";
        std::getline(std::cin, data);
        sk.send_msg(data);
        if (data == "0") createNewGame();
        else if (data == "1") joinGame();
        else std::cout << "Pelotudo pone un numero bien una sola cosa te pido\n";
    }
}

void ConfigChecker::createNewGame() {
    while (true) {
        std::string data;
        std::cout << "Ingrese jugadores/bots/tiempo/id_mapa: ";
        std::getline(std::cin, data);
        sk.send_msg(data);

        std::string answer;
        sk.recv_msg(answer);
        std::cout << "Respuesta: " << answer << "\n";
        if (answer == "1\n") break;
    }
    /*
    while(true) {
        std::string answer;
        sk.recv_msg(answer);
        sleep(1);
    }*/
}

void ConfigChecker::joinGame() {
    while (true) {

        std::string games;
        sk.recv_msg(games);
        std::cout << "Los juegos disponibles son: " << games << "\n";

        std::string data;
        std::cout << "Ingrese el id del juego: ";
        std::getline(std::cin, data);
        sk.send_msg(data);

        std::string answer;
        sk.recv_msg(answer);
        std::cout << "Respuesta: " << answer << "\n";
        if (answer == "1\n") break;
    }
    /*
    while(true) {
        std::string answer;
        sk.recv_msg(answer);
        sleep(1);
    }*/
}

std::string ConfigChecker::getHost() {
    QLineEdit* host_line = findChild<QLineEdit*>("hostLine");
    return host_line->text().toStdString();
}

std::string ConfigChecker::getPort() {
    QLineEdit* port_line = findChild<QLineEdit*>("portLine");
    return port_line->text().toStdString().c_str();
}

void ConfigChecker::connectEvents(){
    QCommandLinkButton* button = findChild<QCommandLinkButton*>("connectButton");
    connect(button, &QCommandLinkButton::clicked,this, &ConfigChecker::lookForServer);

}

void ConfigChecker::showConnectionError() {
    QWidget *error_widget = findChild<QWidget*>("errorWidget");
    QCommandLinkButton* ok_button = findChild<QCommandLinkButton*>("okButton");
    // connect(ok_button, &QPushButton::clicked, error_widget, error_widget->close());
    error_widget->show();
    error_widget->setEnabled(true);
    // qDebug("show");
}

void ConfigChecker::showLobby() {

}
