#include "clientQT/config_checker.h"
#include "ui_connect.h"

#define CREATE_GAME "0"
#define JOIN_GAME "1"
#define MAPS_PATH "../ClientQT/maps/"
#define SUCCESS "2"
#define ERROR "3"


ConfigChecker::ConfigChecker(QMainWindow *parent) : QMainWindow(parent), sk(-1) {
    Ui::ConfigChecker checker;
    checker.setupUi(this);
    hideWidget("connectionWidget");
    hideWidget("errorWidget");
    hideWidget("parametersWidget");
    hideWidget("createConfirmButton");
    hideWidget("joinConfirmButton");
    hideWidget("joinWidget");
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
    data = getSpinContent("minPlayersSpin") + "/" + getSpinContent("maxPlayersSpin") + "/" + getSpinContent("botsSpin") + "/" + getSpinContent("timeSpin");
    //qDebug(data.c_str());
    sk.send_msg(data);
    data = getComboContent("mapCombo");
    //qDebug(data.c_str());
    sk.send_msg(data);
    std::string answer;
    sk.recv_msg(answer);
    std::cout << "Respuesta: " << answer << "\n";
}

void ConfigChecker::showParameters() {
    hideWidget("connectionWidget");
    showWidget("parametersWidget");
    showWidget("createConfirmButton");

    QComboBox *join_combo = findChild<QComboBox*>("mapCombo");
    QSpinBox *max_players_spin = findChild<QSpinBox*>("maxPlayersSpin");
    join_combo->addItems(readAllMaps());
    try {
        MapParser parser(MAPS_PATH + join_combo->currentText().toStdString());
        max_players_spin->setMinimum(1);
        max_players_spin->setMaximum(parser.getSpecificCategory("players").size());
    } catch (YAML::ParserException) {
    } catch (YAML::BadFile) {
    };
}

void ConfigChecker::showIdSelection() {
    hideWidget("connectionWidget");
    hideWidget("createConfirmButton");
    showWidget("joinWidget");
    showWidget("joinConfirmButton");
    sk.send_msg(JOIN_GAME);
    std::string games;
    sk.recv_msg(games);
    //join_combo->addItem(QString(games.c_str()));
}

void ConfigChecker::joinGame() {
    qDebug("AFUERA DEs READ ALL MAPS");
    std::string data;
    QComboBox *join_combo = findChild<QComboBox*>("idCombo");
    data = join_combo->currentText().toStdString();
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

std::string ConfigChecker::getLineContent(const char *line_name) {
    QLineEdit* line = findChild<QLineEdit*>(line_name);
    return line->text().toStdString();
}

std::string ConfigChecker::getSpinContent(const char *spin_name) {
    QSpinBox* spin = findChild<QSpinBox*>(spin_name);
    return std::to_string(spin->value());
}

std::string ConfigChecker::getComboContent(const char *combo_name) {
    QComboBox* combo = findChild<QComboBox*>(combo_name);
    return combo->currentText().toStdString();
}

void ConfigChecker::connectEvents(){
    QWidget *error_widget = findChild<QWidget*>("errorWidget");
    QCommandLinkButton* connect_button = findChild<QCommandLinkButton*>("connectButton");
    QPushButton* ok_button = findChild<QPushButton*>("okButton");
    QPushButton* create_button = findChild<QPushButton*>("createButton");
    QPushButton* join_button = findChild<QPushButton*>("joinButton");
    QCommandLinkButton* create_confirm_button = findChild<QCommandLinkButton*>("createConfirmButton");
    QCommandLinkButton* join_confirm_button = findChild<QCommandLinkButton*>("joinConfirmButton");

    connect(join_confirm_button, &QCommandLinkButton::clicked, this, &ConfigChecker::joinGame);
    connect(create_confirm_button, &QCommandLinkButton::clicked, this, &ConfigChecker::createNewGame);
    connect(ok_button, SIGNAL(clicked()), error_widget, SLOT(close()));
    connect(connect_button, &QPushButton::clicked,this, &ConfigChecker::lookForServer);
    connect(create_button, &QPushButton::clicked,this, &ConfigChecker::showParameters);
    connect(join_button, &QCommandLinkButton::clicked,this, &ConfigChecker::showIdSelection);

}

void ConfigChecker::showConnectionError() {
    showWidget("errorWidget");
    // qDebug("show");
}

void ConfigChecker::showLobby() {

}

QStringList ConfigChecker::readAllMaps() {
    QStringList map_names;
    if (auto dir = opendir(MAPS_PATH)) {
        while (auto f = readdir(dir)) {
            if (f->d_name[0] == '.')
                continue;
            map_names << f->d_name;
        }
        closedir(dir);
    }
    return map_names;
}
