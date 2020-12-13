#include <iostream>
#include <fstream>
#include <unordered_map>
#include <QFileDialog>
#include "yaml-cpp/yaml.h"
#include "editor/editor.h"
#include "server/map_parser.h"
#include "ui_editor.h"

#define DEF_HEIGHT 7
#define DEF_WIDTH 7


struct Coordinate { int x; int y; Coordinate(int coord_x, int coord_y) : x(coord_x), y(coord_y) {}};

YAML::Emitter& operator << (YAML::Emitter& out, const Coordinate& coord) {
    out << YAML::Flow;
    out << YAML::BeginSeq << coord.x << coord.y << YAML::EndSeq;
    return out;
}

Editor::Editor(QMainWindow *parent) : QMainWindow(parent) {
    Ui::Editor editor;
    editor.setupUi(this);
    auto *load = new QAction("Load map", this);
    auto *save = new QAction("Save Map", this);
    auto *quit = new QAction("Quit", this);
    save->setShortcuts(QKeySequence::Save);
    load->setShortcuts(QKeySequence::Open);
    quit->setShortcuts(QKeySequence::Quit);
    QMenu *file = menuBar()->addMenu("File");
    file->addAction(load);
    file->addAction(save);
    file->addAction(quit);
    connect(quit, &QAction::triggered, this, QApplication::quit);
    connect(load, &QAction::triggered, this, &Editor::loadMap);
    connect(save, &QAction::triggered, this, &Editor::exportMap);
    createMapGrid();
    connectEvents();
}

void Editor::loadMap() {
    MapParser parser(getYamlPath());
    std::vector<std::string> categories;
    QPixmap wood_pix("../client_src/resources/walls/wall_3.gif");
    QPixmap stone_pix("../client_src/resources/walls/grey_wall.jpg");
    QPixmap blue_pix("../client_src/resources/blueWall.png");
    QPixmap rpg_pix("../client_src/resources/rpg.png");
    QPixmap chain_pix("../client_src/resources/chainGun.png");
    QPixmap machine_pix("../client_src/resources/machineGun.png");
    QPixmap locked_pix("../client_src/resources/lockedDoor.png");
    QPixmap barrel_pix("../client_src/resources/barrel.png");

    const char *wood_wall = "wood_wall";
    const char *stone_wall = "stone_wall";
    const char *blue_wall = "blue_wall";
    const char *rpg_gun = "rpg_gun";
    const char *chain_gun = "chain_gun";
    const char *machine_gun = "machine_gun";
    const char *locked_door = "locked_door";
    const char *barrel = "barrel";

    QIcon wood_icon(wood_pix);
    QIcon stone_icon(stone_pix);
    QIcon blue_icon(blue_pix);
    QIcon rpg_icon(rpg_pix);
    QIcon chain_icon(chain_pix);
    QIcon machine_icon(machine_pix);
    QIcon locked_icon(locked_pix);
    QIcon barrel_icon(barrel_pix);

    QGridLayout* map_grid = findChild<QGridLayout*>("mapGrid");
    categories.push_back("scenarios");
    categories.push_back("items");
    categories.push_back("players");

    for(auto &category: categories){
        for(auto &items: parser.getCategory(category)){
            for(auto &positions: items.second){
                QPushButton* button = qobject_cast<QPushButton*>(map_grid->itemAtPosition(positions.first, positions.second)->widget());
                if (items.first == "wood_wall") updateGridButton(button, wood_icon, wood_wall);
                if (items.first == "stone_wall") updateGridButton(button, stone_icon, stone_wall);
                if (items.first == "blue_wall") updateGridButton(button, blue_icon, blue_wall);
                if (items.first == "rpg_gun") updateGridButton(button, rpg_icon, rpg_gun);
                if (items.first == "chain_gun") updateGridButton(button, chain_icon, chain_gun);
                if (items.first == "machine_gun") updateGridButton(button, machine_icon, machine_gun);
                if (items.first == "locked_door") updateGridButton(button, locked_icon, locked_door);
                if (items.first == "barrel") updateGridButton(button, barrel_icon, barrel);

            }
        }
    }
}


void Editor::createMapGrid() {
    QPixmap pixmap("../client_src/resources/empty.png");
    QIcon ButtonIcon(pixmap);
    QPixmap wood_pix("../client_src/resources/wall_3.gif");
    const char *wood_wall = "Wood wall";
    QIcon wood_icon(wood_pix);
    QGridLayout* mapGrid = findChild<QGridLayout*>("mapGrid");
    for (int i = 0; i < DEF_HEIGHT; ++i) {
        for (int j = 0; j < DEF_WIDTH; ++j) {
            QPushButton* buttonGrid = new QPushButton();
            QMenu* menu = createGridButtonMenu(buttonGrid);
            buttonGrid->setProperty("texture", "empty");
            buttonGrid->setMenu(menu);
            buttonGrid->setIcon(ButtonIcon);
            buttonGrid->setIconSize(pixmap.rect().size());
            // connect(buttonGrid, ,this, std::bind(&Editor::updateGridButton, this, buttonGrid, wood_icon, wood_wall));
            mapGrid->addWidget(buttonGrid, i, j);
        }
    }

}

QMenu* Editor::createGridButtonMenu(QPushButton *button) {
    QPixmap wood_pix("../client_src/resources/walls/wall_3.gif");
    QPixmap stone_pix("../client_src/resources/walls/grey_wall.jpg");
    QPixmap blue_pix("../client_src/resources/blueWall.png");
    QPixmap rpg_pix("../client_src/resources/rpg.png");
    QPixmap chain_pix("../client_src/resources/chainGun.png");
    QPixmap machine_pix("../client_src/resources/machineGun.png");
    QPixmap locked_pix("../client_src/resources/lockedDoor.png");
    QPixmap barrel_pix("../client_src/resources/barrel.png");

    const char *wood_wall = "wood_wall";
    const char *stone_wall = "stone_wall";
    const char *blue_wall = "blue_wall";
    const char *rpg_gun = "rpg_gun";
    const char *chain_gun = "chain_gun";
    const char *machine_gun = "machine_gun";
    const char *locked_door = "locked_door";
    const char *barrel = "barrel";

    QIcon wood_icon(wood_pix);
    QIcon stone_icon(stone_pix);
    QIcon blue_icon(blue_pix);
    QIcon rpg_icon(rpg_pix);
    QIcon chain_icon(chain_pix);
    QIcon machine_icon(machine_pix);
    QIcon locked_icon(locked_pix);
    QIcon barrel_icon(barrel_pix);

    QMenu* menu = new QMenu();
    QAction* wood_action = menu->addAction(wood_icon, wood_wall);
    QAction* stone_action = menu->addAction(stone_icon, stone_wall);
    QAction* blue_action = menu->addAction(blue_icon, blue_wall);
    QAction* rpg_action = menu->addAction(rpg_icon, rpg_gun);
    QAction* chain_action = menu->addAction(chain_icon, chain_gun);
    QAction* machine_action = menu->addAction(machine_icon, machine_gun);
    QAction* locked_action = menu->addAction(locked_icon, locked_door);
    QAction* barrel_action = menu->addAction(barrel_icon, barrel);

    connect(wood_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, wood_icon, wood_wall));
    connect(stone_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, stone_icon, stone_wall));
    connect(blue_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, blue_icon, blue_wall));
    connect(rpg_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, rpg_icon, rpg_gun));
    connect(chain_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, chain_icon, chain_gun));
    connect(machine_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, machine_icon, machine_gun));
    connect(locked_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, locked_icon, locked_door));
    connect(barrel_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, barrel_icon, barrel));

    return menu;
}

void Editor::updateGridButton(QPushButton *button, QIcon &icon, const char *texture) {
    button->setIcon(icon);
    button->setProperty("texture", QVariant(texture));
}

YAML::Emitter& operator << (YAML::Emitter& out, const std::pair<int, int>& pair) {
    out << YAML::Flow << YAML::BeginSeq << pair.first << pair.second << YAML::EndSeq;
    return out;
}

YAML::Emitter& operator << (YAML::Emitter& out, const std::vector<std::pair<int, int>>& v) {
    out << YAML::Flow << YAML::BeginSeq;
    for (int i = 0; i < v.size(); ++i) {
        out << v[i];
    }
    return out;
}

void Editor::exportMap() {
    /* Height and width input */
    QLineEdit* inputHeight = findChild<QLineEdit*>("inputHeight");
    QLineEdit* inputWidth = findChild<QLineEdit*>("inputWidth");
    QString qHeight= QString("%1").arg(inputHeight->text());
    QString qWidth = QString("%1").arg(inputWidth->text());
    std::string height = qHeight.toStdString();
    std::string width = qWidth.toStdString();
    if (height.empty()) height = "7";
    if (width.empty()) width = "7";

    std::vector<std::pair<int, int>> wood_positions;
    std::vector<std::pair<int, int>> stone_positions;
    std::vector<std::pair<int, int>> blue_positions;
    std::vector<std::pair<int, int>> rpg_positions;
    std::vector<std::pair<int, int>> chain_positions;
    std::vector<std::pair<int, int>> machine_positions;
    std::vector<std::pair<int, int>> locked_positions;
    std::vector<std::pair<int, int>> barrel_positions;

    /* Map input */
    QGridLayout* mapGrid = findChild<QGridLayout*>("mapGrid");
    for (int i = 0; i < mapGrid->rowCount(); ++i) {
        for (int j = 0; j < mapGrid->columnCount(); ++j) {
            QPushButton* buttonGrid = qobject_cast<QPushButton*>(mapGrid->itemAtPosition(i, j)->widget());
            std::string variantTexture = buttonGrid->property("texture").toString().toStdString();
            if (variantTexture == "wood_wall") wood_positions.emplace_back(i, j);
            if (variantTexture == "stone_wall") stone_positions.emplace_back(i, j);
            if (variantTexture == "blue_wall") blue_positions.emplace_back(i, j);
            if (variantTexture == "rpg_gun") rpg_positions.emplace_back(i, j);
            if (variantTexture == "chain_gun") chain_positions.emplace_back(i, j);
            if (variantTexture == "machine_gun") machine_positions.emplace_back(i, j);
            if (variantTexture == "locked_door") locked_positions.emplace_back(i, j);
            if (variantTexture == "barrel") barrel_positions.emplace_back(i, j);
        }
    }

    YAML::Emitter out;
    out << YAML::BeginMap;

    out << YAML::Key << "dimensions";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "width" << YAML::Value << width;
    out << YAML::Key << "height" << YAML::Value << height;
    out << YAML::EndMap;

    out << YAML::Key << "scenarios";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "wood_wall";
    out << YAML::Value << wood_positions << YAML::EndSeq;
    out << YAML::Key << "stone_wall";
    out << YAML::Value << stone_positions << YAML::EndSeq;
    out << YAML::Key << "blue_wall";
    out << YAML::Value << blue_positions << YAML::EndSeq;
    out << YAML::Key << "barrel";
    out << YAML::Value << barrel_positions << YAML::EndSeq;
    out << YAML::Key << "locked_door";
    out << YAML::Value << locked_positions << YAML::EndSeq;
    out << YAML::EndMap;


    out << YAML::Key << "items";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "machine_gun";
    out << YAML::Value << machine_positions << YAML::EndSeq;
    out << YAML::Key << "rpg_gun";
    out << YAML::Value << rpg_positions << YAML::EndSeq;
    out << YAML::Key << "chain_gun";
    out << YAML::Value << chain_positions << YAML::EndSeq;
    out << YAML::EndMap;

    out << YAML::Key << "players";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "player1";
    out << YAML::Value << YAML::Flow << YAML::BeginSeq << Coordinate(1, 2) << Coordinate(3, 4) << Coordinate(5, 6) << YAML::EndSeq;
    out << YAML::Key << "bot1";
    out << YAML::Value << YAML::Flow << YAML::BeginSeq << Coordinate(2, 4) << Coordinate(5, 0) << Coordinate(6, 6) << YAML::EndSeq;
    out << YAML::EndMap;

    out << YAML::EndMap;

    std::fstream file(saveYamlPath(), std::ios::out);
    file << out.c_str();
    file.close();
    this->close();
}

void Editor::refreshMapGrid(){
    /* Height and width input */
    QLineEdit* inputHeight = findChild<QLineEdit*>("inputHeight");
    QLineEdit* inputWidth = findChild<QLineEdit*>("inputWidth");
    QString height= QString("%1").arg(inputHeight->text());
    QString width = QString("%1").arg(inputWidth->text());

    QGridLayout* mapGrid = findChild<QGridLayout*>("mapGrid");
    int gridRows = mapGrid->rowCount();
    int gridCols = mapGrid->columnCount();
    int newCols = width.toInt();
    int newRows = height.toInt();
    int rows = gridRows >= newRows? gridRows : newRows;
    int cols = gridCols >= newCols? gridCols : newCols;

    QPixmap pixmap("../client_src/resources/empty.png");
    QIcon ButtonIcon(pixmap);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i < gridRows && j < gridCols) continue;
            QPushButton* buttonGrid = new QPushButton();
            buttonGrid->setIcon(ButtonIcon);
            buttonGrid->setIconSize(pixmap.rect().size());
            QMenu* menu = createGridButtonMenu(buttonGrid);
            buttonGrid->setMenu(menu);
            mapGrid->addWidget(buttonGrid, i, j);
        }
    } // TODO Agregar sacar celdas
}

std::string Editor::saveYamlPath() {
    return QFileDialog::getSaveFileName(this,
                                        tr("Save map"), ".yaml",
                                        tr("YAML file (*.yaml)")).toStdString();
}

std::string Editor::getYamlPath() {
    return QFileDialog::getOpenFileName(this,
                                        tr("Load map"), "",
                                        tr("YAML file (*.yaml)")).toStdString();
}


void Editor::connectEvents() {
    QPushButton* buttonExport = findChild<QPushButton*>("buttonExport");
    connect(buttonExport, &QPushButton::clicked,this, &Editor::exportMap);
    QPushButton* buttonRefresh = findChild<QPushButton*>("buttonRefresh");
    connect(buttonRefresh, &QPushButton::clicked,this, &Editor::refreshMapGrid);
}

