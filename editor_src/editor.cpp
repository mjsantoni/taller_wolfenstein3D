#include <iostream>
#include <fstream>
#include <unordered_map>
#include "yaml-cpp/yaml.h"
#include "editor/editor.h"
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
    createMapGrid();
    connectEvents();
}

void Editor::createMapGrid() {
    QPixmap pixmap("../client_src/resources/empty.png");
    QIcon ButtonIcon(pixmap);
    QGridLayout* mapGrid = findChild<QGridLayout*>("mapGrid");
    for (int i = 0; i < DEF_HEIGHT; ++i) {
        for (int j = 0; j < DEF_WIDTH; ++j) {
            QPushButton* buttonGrid = new QPushButton();
            QMenu* menu = createGridButtonMenu(buttonGrid);
            buttonGrid->setProperty("texture", "empty");
            buttonGrid->setMenu(menu);
            buttonGrid->setIcon(ButtonIcon);
            buttonGrid->setIconSize(pixmap.rect().size());
            mapGrid->addWidget(buttonGrid, i, j);
        }
    }

}

QMenu* Editor::createGridButtonMenu(QPushButton *button) {
    QPixmap woodPix("../client_src/resources/wall_3.gif");
    QPixmap stonePix("../client_src/resources/wall_alt.jpg");
    QPixmap bluePix("../client_src/resources/blueWall.png");
    QPixmap rpgPix("../client_src/resources/rpg.png");
    QPixmap chainPix("../client_src/resources/chainGun.png");
    QPixmap machinePix("../client_src/resources/machineGun.png");
    QPixmap lockedPix("../client_src/resources/lockedDoor.png");
    QPixmap barrelPix("../client_src/resources/barrel.png");

    const char *woodWall = "Wood wall";
    const char *stoneWall = "Stone wall";
    const char *blueWall = "Blue wall";
    const char *rpgGun = "RPG gun";
    const char *chainGun = "Chain gun";
    const char *machineGun = "Machine gun";
    const char *lockedDoor = "Locked door";
    const char *barrelItem = "Barrel item";

    QIcon woodIcon(woodPix);
    QIcon stoneIcon(stonePix);
    QIcon blueIcon(bluePix);
    QIcon rpgIcon(rpgPix);
    QIcon chainIcon(chainPix);
    QIcon machineIcon(machinePix);
    QIcon lockedIcon(lockedPix);
    QIcon barrelIcon(barrelPix);

    QMenu* menu = new QMenu();
    QAction* woodAction = menu->addAction(woodIcon, woodWall);
    QAction* stoneAction = menu->addAction(stoneIcon, stoneWall);
    QAction* blueAction = menu->addAction(blueIcon, blueWall);
    QAction* rpgAction = menu->addAction(rpgIcon, rpgGun);
    QAction* chainAction = menu->addAction(chainIcon, chainGun);
    QAction* machineAction = menu->addAction(machineIcon, machineGun);
    QAction* lockedAction = menu->addAction(lockedIcon, lockedDoor);
    QAction* barrelAction = menu->addAction(barrelIcon, barrelItem);

    connect(woodAction, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, woodIcon, woodWall));
    connect(stoneAction, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, stoneIcon, stoneWall));
    connect(blueAction, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, blueIcon, blueWall));
    connect(rpgAction, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, rpgIcon, rpgGun));
    connect(chainAction, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, chainIcon, chainGun));
    connect(machineAction, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, machineIcon, machineGun));
    connect(lockedAction, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, lockedIcon, lockedDoor));
    connect(barrelAction, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, barrelIcon, barrelItem));
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
    std::vector<std::pair<int, int>> woodPositions;
    std::vector<std::pair<int, int>> stonePositions;
    std::vector<std::pair<int, int>> bluePositions;
    std::vector<std::pair<int, int>> rpgPositions;
    std::vector<std::pair<int, int>> chainPositions;
    std::vector<std::pair<int, int>> machinePositions;
    std::vector<std::pair<int, int>> lockedPositions;
    std::vector<std::pair<int, int>> barrelPositions;

    /* Map input */
    QGridLayout* mapGrid = findChild<QGridLayout*>("mapGrid");
    for (int i = 0; i < mapGrid->rowCount(); ++i) {
        for (int j = 0; j < mapGrid->columnCount(); ++j) {
            QPushButton* buttonGrid = qobject_cast<QPushButton*>(mapGrid->itemAtPosition(i, j)->widget());
            std::string variantTexture = buttonGrid->property("texture").toString().toStdString();
            if (variantTexture == "Wood wall") woodPositions.emplace_back(i, j);
            if (variantTexture == "Stone wall") stonePositions.emplace_back(i, j);
            if (variantTexture == "Blue wall") bluePositions.emplace_back(i, j);
            if (variantTexture == "RPG gun") rpgPositions.emplace_back(i, j);
            if (variantTexture == "Chain gun") chainPositions.emplace_back(i, j);
            if (variantTexture == "Machine gun") machinePositions.emplace_back(i, j);
            if (variantTexture == "Locked door") lockedPositions.emplace_back(i, j);
            if (variantTexture == "Barrel item") barrelPositions.emplace_back(i, j);
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
    out << YAML::Key << "wood wall";
    out << YAML::Value << woodPositions << YAML::EndSeq;
    out << YAML::Key << "stone wall";
    out << YAML::Value << stonePositions << YAML::EndSeq;
    out << YAML::Key << "blue wall";
    out << YAML::Value << bluePositions << YAML::EndSeq;
    out << YAML::Key << "barrel item";
    out << YAML::Value << barrelPositions << YAML::EndSeq;
    out << YAML::Key << "locked door";
    out << YAML::Value << lockedPositions << YAML::EndSeq;
    out << YAML::Key << "machine gun";
    out << YAML::Value << machinePositions << YAML::EndSeq;
    out << YAML::Key << "rpg gun";
    out << YAML::Value << rpgPositions << YAML::EndSeq;
    out << YAML::Key << "chain gun";
    out << YAML::Value << chainPositions << YAML::EndSeq;
    out << YAML::EndMap;

    out << YAML::Key << "players";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "player1";
    out << YAML::Value << YAML::Flow << YAML::BeginSeq << Coordinate(1, 2) << Coordinate(3, 4) << Coordinate(5, 6) << YAML::EndSeq;
    out << YAML::Key << "bot1";
    out << YAML::Value << YAML::Flow << YAML::BeginSeq << Coordinate(2, 4) << Coordinate(5, 7) << Coordinate(6, 6) << YAML::EndSeq;
    out << YAML::EndMap;

    out << YAML::EndMap;
    std::fstream file("../map.yaml", std::ios::out);
    file << out.c_str();
    file.close();
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

void Editor::connectEvents() {
    // Conecto el evento del boton
    QPushButton* buttonExport = findChild<QPushButton*>("buttonExport");
    //exportMap();
    QObject::connect(buttonExport, &QPushButton::clicked,
                     this, &Editor::exportMap);
    QPushButton* buttonRefresh = findChild<QPushButton*>("buttonRefresh");
    //exportMap();
    QObject::connect(buttonRefresh, &QPushButton::clicked,
                     this, &Editor::refreshMapGrid);
}

