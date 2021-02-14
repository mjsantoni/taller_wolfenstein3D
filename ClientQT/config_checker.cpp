#include <QSpinBox>
#include "clientQT/config_checker.h"
#include "ui_connect.h"


ConfigChecker::ConfigChecker(QMainWindow *parent) : QMainWindow(parent), sk(-1) {
    Ui::ConfigChecker checker;
    checker.setupUi(this);
    hideWidget("connectionWidget");
    hideWidget("errorWidget");
    hideWidget("parametersWidget");
    hideWidget("createConfirmButton");
    connectEvents();
}

void ConfigChecker::lookForServer() {
    try {
        NetworkConnection connection(getLineContent("hostLine").c_str(), getLineContent("portLine").c_str());
        sk = std::move(connection);
        server_found = true;
        showWidget("connectionWidget");
        hideWidget("configWidget");
        QCommandLinkButton* connect_button = findChild<QCommandLinkButton*>("connectButton");
        connect_button->close();
    } catch (const NetworkError& e) {
        showConnectionError();
    }
}


void ConfigChecker::hideWidget(const char *widgetName) {
    QWidget *widget = findChild<QWidget*>(widgetName);
    widget->hide();
}

void ConfigChecker::showWidget(const char *widgetName) {
    QWidget *widget = findChild<QWidget*>(widgetName);
    widget->setEnabled(true);
    widget->show();
}

void ConfigChecker::createNewGame() {
    "Ingrese jugadores/bots/tiempo/id_mapa: ";
    std::string data;
    sk.send_msg("0");
    data = getSpinContent("jugadoresSpin") + "/" + getSpinContent("botsSpin") + "/" + getLineContent("tiempoLine") + "/" + getLineContent("mapaLine");
    sk.send_msg(data);
    std::string answer;
    sk.recv_msg(answer);
    std::cout << "Respuesta: " << answer << "\n";
    /*
    while(true) {
        std::string answer;
        sk.recv_msg(answer);
        sleep(1);
    }*/
}

void ConfigChecker::showParameters() {
    hideWidget("connectionWidget");
    showWidget("parametersWidget");
    showWidget("createConfirmButton");
}

void ConfigChecker::joinGame() {
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
    if (answer == "1\n");
    /*
    while(true) {
        std::string answer;
        sk.recv_msg(answer);
        sleep(1);
    }*/
}

std::string ConfigChecker::getLineContent(const char *lineName) {
    QLineEdit* line = findChild<QLineEdit*>(lineName);
    return line->text().toStdString();
}

std::string ConfigChecker::getSpinContent(const char *spinName) {
    QSpinBox* spin = findChild<QSpinBox*>(spinName);
    return std::to_string(spin->value());
}

void ConfigChecker::connectEvents(){
    QWidget *error_widget = findChild<QWidget*>("errorWidget");
    QCommandLinkButton* connect_button = findChild<QCommandLinkButton*>("connectButton");
    QPushButton* ok_button = findChild<QPushButton*>("okButton");
    QPushButton* create_button = findChild<QPushButton*>("createButton");
    QPushButton* join_button = findChild<QPushButton*>("joinButton");
    QCommandLinkButton* create_confirm_button = findChild<QCommandLinkButton*>("createConfirmButton");

    connect(create_confirm_button, &QCommandLinkButton::clicked, this, &ConfigChecker::createNewGame);
    connect(ok_button, SIGNAL(clicked()), error_widget, SLOT(close()));
    connect(connect_button, &QPushButton::clicked,this, &ConfigChecker::lookForServer);
    connect(create_button, &QPushButton::clicked,this, &ConfigChecker::showParameters);
    connect(join_button, &QCommandLinkButton::clicked,this, &ConfigChecker::joinGame);

}

void ConfigChecker::showConnectionError() {
    showWidget("errorWidget");
    // qDebug("show");
}

void ConfigChecker::showLobby() {

}
