#include <iostream>
#include <fstream>
#include <unordered_map>
#include "yaml-cpp/yaml.h"
#include "editor/editor.h"
#include "ui_editor.h"


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
    QPixmap pixmap("../client_src/resources/wall_alt.jpg");
    QIcon ButtonIcon(pixmap);
    QGridLayout* mapGrid = findChild<QGridLayout*>("mapGrid");
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            QPushButton* buttonGrid = new QPushButton();
            QMenu* menu = createGridButtonMenu(buttonGrid);
            buttonGrid->setProperty("texture", "empty");
            buttonGrid->setMenu(menu);
            //QObject::connect(buttonGrid, &QPushButton::clicked, this, &QPushButton::showMenu);
            buttonGrid->setIcon(ButtonIcon);
            buttonGrid->setIconSize(pixmap.rect().size());
            mapGrid->addWidget(buttonGrid, i, j);
        }
    }

}

QMenu* Editor::createGridButtonMenu(QPushButton *button) {
    QPixmap woodPix("../client_src/resources/wall_3.gif");
    QPixmap stonePix("../client_src/resources/wall_alt.jpg");
    std::string stringWood = "Wood wall";
    std::string stringStone = "Stone wall";
    QIcon woodIcon(woodPix);
    QIcon stoneIcon(stonePix);
    QMenu* menu = new QMenu();
    QAction* woodAction = menu->addAction(woodIcon, "Wood wall");
    QAction* stoneAction = menu->addAction(stoneIcon, "Stone wall");
    connect(woodAction, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, woodIcon, stringWood));
    connect(stoneAction, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, stoneIcon, stringStone));
    return menu;
}

void Editor::updateGridButton(QPushButton *button, QIcon &icon, std::string &texture) {
    button->setIcon(icon);
    button->setProperty("texture", "Wood wall");
}

void Editor::exportMap() {

    /* Height and width input */
    QLineEdit* inputHeight = findChild<QLineEdit*>("inputHeight");
    QLineEdit* inputWidth = findChild<QLineEdit*>("inputWidth");
    QString height= QString("%1").arg(inputHeight->text());
    QString width = QString("%1").arg(inputWidth->text());
    std::vector<int> woodPositions;

    /* Map input */
    QGridLayout* mapGrid = findChild<QGridLayout*>("mapGrid");
    for (int i = 0; i < mapGrid->rowCount(); ++i) {
        for (int j = 0; j < mapGrid->columnCount(); ++j) {
            QPushButton* buttonGrid = qobject_cast<QPushButton*>(mapGrid->itemAtPosition(i, j)->widget());
            std::string variantTexture = buttonGrid->property("texture").toString().toStdString();
            if (variantTexture == "Wood wall") woodPositions.emplace_back(i);
        }
    }

    YAML::Emitter out;
    out << YAML::BeginMap;

    out << YAML::Key << "dimensions";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "width" << YAML::Value << height.toStdString();
    out << YAML::Key << "ui_height" << YAML::Value << width.toStdString();
    out << YAML::EndMap;

    out << YAML::Key << "scenarios";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "pared";
    out << YAML::Value << woodPositions << YAML::EndSeq;
    out << YAML::Key << "puerta";
    out << YAML::Value << YAML::Flow << YAML::BeginSeq << Coordinate(2, 4) << Coordinate(5, 7) << Coordinate(6, 6) << YAML::EndSeq;
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

    QPixmap pixmap("../client_src/resources/wall_alt.jpg");
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

