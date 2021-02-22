#include <QtWidgets/QCommandLinkButton>
#include "client/config_checker.h"
#include "ui_connect.h"

#define CREATE_GAME "0"
#define JOIN_GAME "1"
#define MAPS_PATH "../maps/"
#define WINDOW_ICON_PATH "../client_src/resources/menus/windowIcon.png"
#define BACKGROUND_PATH "../client_src/resources/menus/intro2.jpg"
#define SUCCESS "2"
#define ERROR "3"
#define BACK "4"


ConfigChecker::ConfigChecker(std::string &_map_data, QMainWindow *parent) : map_data(_map_data), QMainWindow(parent), sk(-1) {
    Ui::ConfigChecker checker;
    checker.setupUi(this);
    this->setWindowIcon(QIcon(WINDOW_ICON_PATH));
    QPixmap background(BACKGROUND_PATH);
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);

    hideWidget("connectionWidget");
    hideWidget("errorWidget");
    hideWidget("creationError");
    hideWidget("parametersWidget");
    hideWidget("createConfirmButton");
    hideWidget("joinConfirmButton");
    hideWidget("backButton");
    hideWidget("joinWidget");
    connectEvents();
}

void ConfigChecker::lookForServer() {
    try {
        NetworkConnection connection(getLineContent("hostLine").c_str(), getLineContent("portLine").c_str());
        sk = std::move(connection);
        showWidget("connectionWidget");
        hideWidget("configWidget");
        QCommandLinkButton* connect_button = findChild<QCommandLinkButton*>("connectButton");
        connect_button->close();
        hideWidget("errorWidget");
    } catch (const NetworkError& e) {
        showWidget("errorWidget");
    }
}


void ConfigChecker::hideWidget(const char *widgetName) {
    QWidget *widget = findChild<QWidget*>(widgetName);
    if (widget)
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
    sk.send_msg(CREATE_GAME);
    data = getSpinContent("minPlayersSpin") + "/" + getSpinContent("maxPlayersSpin") + "/" + getSpinContent("botsSpin") + "/" + getSpinContent("timeSpin");
    sk.send_msg(data);
    data = getComboContent("mapCombo");
    sk.send_msg(data);
    std::string answer;
    sk.recv_msg(answer);
    if (answer == SUCCESS) {
        map_data = data;
        this->close();
    } else {
        showError("Error creating the game");
    }
}

void ConfigChecker::showParameters() {
    QComboBox *join_combo = findChild<QComboBox*>("mapCombo");
    QSpinBox *max_players_spin = findChild<QSpinBox*>("maxPlayersSpin");
    QSpinBox *min_players_spin = findChild<QSpinBox*>("minPlayersSpin");
    QSpinBox *bots_spin = findChild<QSpinBox*>("botsSpin");
    if (!backed) join_combo->addItems(readAllMaps());
    showWidget("backButton");
    if (join_combo->currentText().toStdString().empty()) {
        showError("No maps to create a game");
        return;
    }

    hideWidget("connectionWidget");
    showWidget("parametersWidget");
    showWidget("createConfirmButton");

    try {
        MapParser parser(MAPS_PATH + join_combo->currentText().toStdString());
        int max_players_size = parser.getSpecificCategory("players").size();
        max_players_spin->setMinimum(1);
        bots_spin->setMaximum(max_players_size-1);
        min_players_spin->setMaximum(max_players_size);
        max_players_spin->setMaximum(max_players_size);
    } catch (YAML::ParserException) {
        showError("Error en el parseo del mapa");
    } catch (YAML::BadFile) {
        showError("Error en el archivo del mapa");
    }
}

void ConfigChecker::showIdSelection() {
    hideWidget("connectionWidget");
    hideWidget("createConfirmButton");
    showWidget("joinWidget");
    showWidget("joinConfirmButton");
    QComboBox *id_combo = findChild<QComboBox*>("idCombo");
    showWidget("backButton");
    sk.send_msg(JOIN_GAME);
    std::string games;
    sk.recv_msg(games);
    QStringList maps_names;
    while (games != SUCCESS){
        if (!backed){
            maps_names << games.c_str();
        }
        games.clear();
        sk.recv_msg(games);
    }
    if (maps_names.size() > 0){
        id_combo->addItems(maps_names);
    }
}

void ConfigChecker::joinGame() {
    QComboBox *id_combo = findChild<QComboBox*>("idCombo");
    if (id_combo->currentText().toStdString().empty()) {
        showError("No matches to join");
        return;
    }
    std::stringstream ss(id_combo->currentText().toStdString());
    std::string map_name = ss.str().substr(0, ss.str().find('/')) + ".yaml";
    std::string id = ss.str().substr(ss.str().find('/') + 1);
    std::string answer;
    //try
    sk.send_msg(id);
    sk.recv_msg(answer);
    if (answer == SUCCESS){
        map_data = map_name;
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
    QCommandLinkButton* connect_button = findChild<QCommandLinkButton*>("connectButton");
    QCommandLinkButton* join_confirm_button = findChild<QCommandLinkButton*>("joinConfirmButton");
    QCommandLinkButton* create_confirm_button = findChild<QCommandLinkButton*>("createConfirmButton");
    QPushButton* ok_button = findChild<QPushButton*>("okButton");
    QPushButton* back_button = findChild<QPushButton*>("backButton");
    QPushButton* create_button = findChild<QPushButton*>("createButton");
    QPushButton* join_button = findChild<QPushButton*>("joinButton");
    QSpinBox *max_players_spin = findChild<QSpinBox*>("maxPlayersSpin");
    QSpinBox *min_players_spin = findChild<QSpinBox*>("minPlayersSpin");
    QSpinBox *bots_spin = findChild<QSpinBox*>("botsSpin");
    QComboBox *map_box = findChild<QComboBox*>("mapCombo");

    connect(join_confirm_button, &QCommandLinkButton::clicked, this, &ConfigChecker::joinGame);
    connect(create_confirm_button, &QCommandLinkButton::clicked, this, &ConfigChecker::createNewGame);
    connect(back_button, &QCommandLinkButton::clicked, this, &ConfigChecker::backToMenu);
    connect(ok_button, SIGNAL(clicked()), error_widget, SLOT(close()));
    connect(connect_button, &QPushButton::clicked,this, &ConfigChecker::lookForServer);
    connect(create_button, &QPushButton::clicked,this, &ConfigChecker::showParameters);
    connect(join_button, &QCommandLinkButton::clicked,this, &ConfigChecker::showIdSelection);
    connect(min_players_spin, QOverload<int>::of(&QSpinBox::valueChanged), this, &ConfigChecker::updateBotsSpin);
    connect(max_players_spin, QOverload<int>::of(&QSpinBox::valueChanged), this, &ConfigChecker::updateMaximums);
    connect(map_box, &QComboBox::currentTextChanged, this, &ConfigChecker::updateMaxPlayerMap);
    connect(bots_spin, QOverload<int>::of(&QSpinBox::valueChanged), this, &ConfigChecker::updateMinSpin);
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
    QLabel *label = findChild<QLabel*>("errorLabel");
    label->setText(QString(string));
    widget->setEnabled(true);
    widget->show();
}

void ConfigChecker::updateBotsSpin() {\
    QSpinBox *max_players_spin = findChild<QSpinBox*>("maxPlayersSpin");
    QSpinBox *min_players_spin = findChild<QSpinBox*>("minPlayersSpin");

    if (max_players_spin->value() < min_players_spin->value()) {
        max_players_spin->setValue(min_players_spin->value());
    }
    updateSpin("botsSpin", "minPlayersSpin");
}

void ConfigChecker::updateMaxPlayerMap() {
    QSpinBox *max_players_spin = findChild<QSpinBox*>("maxPlayersSpin");
    QSpinBox *min_players_spin = findChild<QSpinBox*>("minPlayersSpin");
    QSpinBox *bots_spin = findChild<QSpinBox*>("botsSpin");
    QComboBox *map_box = findChild<QComboBox*>("mapCombo");
    MapParser parser(MAPS_PATH + map_box->currentText().toStdString());
    int max_players_size = parser.getSpecificCategory("players").size();
    max_players_spin->setMaximum(max_players_size);

    int value_max = max_players_spin->value();
    min_players_spin->setMaximum(value_max);
    if (value_max - 1 < 0)
        value_max = 1;
    bots_spin->setMaximum(value_max - 1);
}

void ConfigChecker::updateMinSpin() {
    updateSpin( "minPlayersSpin", "botsSpin");
}

void ConfigChecker::updateSpin(const char *to_update, const char *updater) {
    QSpinBox *max_players_spin = findChild<QSpinBox*>("maxPlayersSpin");
    QSpinBox *update = findChild<QSpinBox*>(to_update);
    QSpinBox *updateree = findChild<QSpinBox*>(updater);

    if (update->value() + updateree->value() > max_players_spin->value())
        update->setValue(max_players_spin->value() - updateree->value());
}

void ConfigChecker::updateMaximums() {
    QSpinBox *max_players_spin = findChild<QSpinBox*>("maxPlayersSpin");
    QSpinBox *min_players_spin = findChild<QSpinBox*>("minPlayersSpin");
    QSpinBox *bots_spin = findChild<QSpinBox*>("botsSpin");
    int value_max = max_players_spin->value();

    if (max_players_spin->value() == min_players_spin->value()) {
        bots_spin->setValue(bots_spin->value()-1);
    }

    bots_spin->setMaximum(value_max - 1);
    min_players_spin->setMaximum(value_max);

}

void ConfigChecker::backToMenu() {
    hideWidget("configWidget");
    hideWidget("errorWidget");
    hideWidget("creationError");
    hideWidget("parametersWidget");
    hideWidget("createConfirmButton");
    hideWidget("joinConfirmButton");
    hideWidget("joinWidget");
    hideWidget("backButton");
    showWidget("connectionWidget");

    backed = true;

    sk.send_msg(BACK);
}

NetworkConnection ConfigChecker::getConnection() {
    return std::move(sk);
}