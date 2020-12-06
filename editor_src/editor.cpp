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
    connectEvents();
}

void Editor::exportMap() {

    /* Height and width input */
    QLineEdit* inputHeight = findChild<QLineEdit*>("inputHeight");
    QLineEdit* inputWidth = findChild<QLineEdit*>("inputWidth");
    QLabel* labelHeight = findChild<QLabel*>("labelHeight");
    QLabel* labelWidth = findChild<QLabel*>("labelWidth");
    QString height= QString("%1").arg(inputHeight->text());
    QString width = QString("%1").arg(inputWidth->text());

    YAML::Emitter out;
    out << YAML::BeginMap;

    out << YAML::Key << "dimensions";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "width" << YAML::Value << height.toStdString();
    out << YAML::Key << "height" << YAML::Value << width.toStdString();
    out << YAML::EndMap;

    out << YAML::Key << "scenarios";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "pared";
    out << YAML::Value << YAML::Flow << YAML::BeginSeq << Coordinate(1, 2) << Coordinate(3, 4) << Coordinate(5, 6) << YAML::EndSeq;
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

void Editor::connectEvents() {
    // Conecto el evento del boton
    QPushButton* buttonExport = findChild<QPushButton*>("buttonExport");
    //exportMap();
    QObject::connect(buttonExport, &QPushButton::clicked,
                     this, &Editor::exportMap);
}

