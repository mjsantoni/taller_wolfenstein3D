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
    hideWidget("creationError");
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
        showWidget("errorWidget");
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
    qDebug(answer.c_str());
    if (answer == "2") {
        //run client normal TODO
        this->close();
    } else {
        showError("Error creating the game");
    }
}

void ConfigChecker::showParameters() {
    hideWidget("connectionWidget");
    showWidget("parametersWidget");
    showWidget("createConfirmButton");

    QComboBox *join_combo = findChild<QComboBox*>("mapCombo");
    QSpinBox *max_players_spin = findChild<QSpinBox*>("maxPlayersSpin");
    QSpinBox *min_players_spin = findChild<QSpinBox*>("minPlayersSpin");
    join_combo->addItems(readAllMaps());
    try {
        MapParser parser(MAPS_PATH + join_combo->currentText().toStdString());
        int max_players_size = parser.getSpecificCategory("players").size();
        max_players_spin->setMinimum(1);
        min_players_spin->setMaximum(max_players_size);
        max_players_spin->setMaximum(max_players_size);
    } catch (YAML::ParserException) {
    } catch (YAML::BadFile) {
    };
}

void ConfigChecker::showIdSelection() {
    hideWidget("connectionWidget");
    hideWidget("createConfirmButton");
    showWidget("joinWidget");
    showWidget("joinConfirmButton");
    QComboBox *id_combo = findChild<QComboBox*>("idCombo");

    sk.send_msg(JOIN_GAME);
    std::string games;
    sk.recv_msg(games);
    QStringList maps_names;
    while (games != SUCCESS){
        maps_names << games.c_str();
        games.clear();
        sk.recv_msg(games);
    }
    id_combo->addItems(maps_names);
}

void ConfigChecker::joinGame() {
    std::string data;
    QComboBox *id_combo = findChild<QComboBox*>("idCombo");
    std::stringstream ss(id_combo->currentText().toStdString());
    std::string s;
    int i = 0;
    while (std::getline(ss, s, '/')) {
        if (s.empty()) continue;
        if (i > 0) data.push_back(s[i-1]);
        i++;
    }
    sk.send_msg(data);
    std::string answer;
    sk.recv_msg(answer);
    if (answer == SUCCESS){
        // run del cliente normal TODO
        this->close();
    }
    else showError("Error en login");
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
    QWidget *creation_error_widget = findChild<QWidget*>("creationError");
    QCommandLinkButton* connect_button = findChild<QCommandLinkButton*>("connectButton");
    QPushButton* ok_button = findChild<QPushButton*>("okButton");
    QPushButton* ok_creation_button = findChild<QPushButton*>("okCreationButton");
    QPushButton* create_button = findChild<QPushButton*>("createButton");
    QPushButton* join_button = findChild<QPushButton*>("joinButton");
    QCommandLinkButton* create_confirm_button = findChild<QCommandLinkButton*>("createConfirmButton");
    QCommandLinkButton* join_confirm_button = findChild<QCommandLinkButton*>("joinConfirmButton");
    QSpinBox *max_players_spin = findChild<QSpinBox*>("maxPlayersSpin");
    QSpinBox *min_players_spin = findChild<QSpinBox*>("minPlayersSpin");
    QSpinBox *bots_spin = findChild<QSpinBox*>("botsSpin");

    connect(join_confirm_button, &QCommandLinkButton::clicked, this, &ConfigChecker::joinGame);
    connect(create_confirm_button, &QCommandLinkButton::clicked, this, &ConfigChecker::createNewGame);
    connect(ok_button, SIGNAL(clicked()), error_widget, SLOT(close()));
    connect(ok_creation_button, SIGNAL(clicked()), creation_error_widget, SLOT(close()));
    connect(connect_button, &QPushButton::clicked,this, &ConfigChecker::lookForServer);
    connect(create_button, &QPushButton::clicked,this, &ConfigChecker::showParameters);
    connect(join_button, &QCommandLinkButton::clicked,this, &ConfigChecker::showIdSelection);
    //connect(bots_spin, &QSpinBox::valueChanged, min_players_spin, std::bind(&QSpinBox::setValue, this, max_players_spin->value()-bots_spin->value()));
}

void ConfigChecker::showLobby() {

}

QStringList ConfigChecker::readAllMaps() {
    QStringList maps_names;
    if (auto dir = opendir(MAPS_PATH)) {
        while (auto f = readdir(dir)) {
            if (f->d_name[0] == '.')
                continue;
            maps_names << f->d_name;
        }
        closedir(dir);
    }
    return maps_names;
}

void ConfigChecker::showError(const char *string) {
    QWidget *widget = findChild<QWidget*>("errorWidget");
    QLabel *label = findChild<QLabel*>("errorLAbel");
    label->setText(QString(string));
    widget->setEnabled(true);
    widget->show();
}
