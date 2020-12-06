#include <iostream>
#include "editor/editor.h"
#include "ui_editor.h"

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
    QString stringHeight = inputHeight->text();
    QString stringWidth = inputWidth->text();
    QString height= QString("Height: %1").arg(stringHeight);
    QString width = QString("Width: %1").arg(stringWidth);
    labelHeight->setText(height);
    labelWidth->setText(width);


}

void Editor::connectEvents() {
    // Conecto el evento del boton
    QPushButton* buttonExport = findChild<QPushButton*>("buttonExport");
    //exportMap();
    QObject::connect(buttonExport, &QPushButton::clicked,
                     this, &Editor::exportMap);
}

/*void yamlTestOut() {

    std::vector <int> positions;
    for(int i = 0; i < 10; ++i) {
        positions.push_back(i);
    }
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "Jugadores";
    out << YAML::Value << YAML::Flow << positions;
    out << YAML::EndMap;

    std::fstream config("../yamlTest.yaml", std::ios::out);
    std::cout << out.c_str();
    config << out.c_str();
    config.close();
}*/
