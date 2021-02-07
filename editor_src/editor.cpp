#include <iostream>
#include <fstream>
#include <unordered_map>
#include <QFileDialog>
#include "yaml-cpp/yaml.h"
#include "editor/editor.h"
#include "server/map_parser.h"
#include "ui_editor.h"
#include "editor/QGridButton.h"

#define DEF_HEIGHT 15
#define DEF_WIDTH 15


struct Coordinate { int x; int y; Coordinate(int coord_x, int coord_y) : x(coord_x), y(coord_y) {}};

YAML::Emitter& operator << (YAML::Emitter& out, const Coordinate& coord) {
    out << YAML::Flow;
    out << YAML::BeginSeq << coord.x << coord.y << YAML::EndSeq;
    return out;
}

Editor::Editor(QMainWindow *parent) : QMainWindow(parent) {
    Ui::Editor editor;
    editor.setupUi(this);
    setAcceptDrops(true);
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
    connect(load, &QAction::triggered, this, std::bind(&Editor::loadMap, this, ""));
    connect(save, &QAction::triggered, this, &Editor::exportMap);
    createMapGrid();
    createTextureGrid();
    connectEvents();
}

void Editor::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void Editor::dropEvent(QDropEvent *e){
    const QMimeData* mimeData = e->mimeData();
            foreach (const QUrl &url, mimeData->urls()) {
            QString fileName = url.toLocalFile();
            loadMap(fileName.toStdString());
        }
    
}


void Editor::dragMoveEvent(QDragMoveEvent* event) {
    // if some actions should not be usable, like move, this code must be adopted
    event->acceptProposedAction();
}

void Editor::dragLeaveEvent(QDragLeaveEvent* event)
{
    event->accept();
}

void Editor::loadMap(std::string path) {
    if(path.empty()) MapParser parser(getYamlPath());
    MapParser parser(path);
    std::vector<std::string> categories;
    QPixmap wood_pix("../client_src/resources/walls/brown_wall.png");
    QPixmap gray_pix("../client_src/resources/walls/gray_wall.jpg");
    QPixmap blue_pix("../client_src/resources/walls/blue_wall.png");
    QPixmap stone_pix("../client_src/resources/walls/stone_wall.png");
    QPixmap rpg_pix("../client_src/resources/items/rocket_launcher.png");
    QPixmap chain_pix("../client_src/resources/items/chain_cannon.png");
    QPixmap machine_pix("../client_src/resources/items/machine_gun.png");
    QPixmap locked_pix("../client_src/resources/items/blood.png");
    QPixmap barrel_pix("../client_src/resources/items/bullets.png");

    const char *wood_wall = "wood_wall";
    const char *gray_wall = "gray_wall";
    const char *blue_wall = "blue_wall";
    const char *stone_wall = "stone_wall";
    const char *rpg_gun = "rpg_gun";
    const char *chain_gun = "chain_gun";
    const char *machine_gun = "machine_gun";
    const char *locked_door = "locked_door";
    const char *barrel = "barrel";

    QIcon wood_icon(wood_pix);
    QIcon gray_icon(gray_pix);
    QIcon blue_icon(blue_pix);
    QIcon stone_icon(stone_pix);
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
                QGridButton* button = qobject_cast<QGridButton*>(map_grid->itemAtPosition(positions.first, positions.second)->widget());
                if (items.first == "wood_wall") updateGridButton(button, wood_icon, wood_wall);
                if (items.first == "gray_wall") updateGridButton(button, gray_icon, gray_wall);
                if (items.first == "blue_wall") updateGridButton(button, blue_icon, blue_wall);
                if (items.first == "stone_wall") updateGridButton(button, stone_icon, stone_wall);
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
    QPixmap wood_pix("../client_src/resources/walls/brown_wall.png");
    QCursor cursor;
    QIcon icon(cursor.pixmap());
    QGridLayout* mapGrid = findChild<QGridLayout*>("mapGrid");
    QWidget* scrollAreaContent = new QWidget;
    scrollAreaContent->setStyleSheet("QWidget{background-color: black;}");
    scrollAreaContent->setLayout( mapGrid );
    QScrollArea* scrollArea = findChild<QScrollArea*>("scrollArea");
    scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    scrollArea->setWidgetResizable( true );
    scrollArea->setWidget( scrollAreaContent );
    for (int i = 0; i < DEF_HEIGHT; ++i) {
        for (int j = 0; j < DEF_WIDTH; ++j) {
            QGridButton* buttonGrid = new QGridButton();
            QMenu* menu = createGridButtonMenu(buttonGrid);
            buttonGrid->setStyleSheet("QGridButton::menu-indicator{width:0px;}");
            buttonGrid->setProperty("texture", "empty");
            buttonGrid->setMenu(menu);
            buttonGrid->cursor();
            buttonGrid->setIcon(ButtonIcon);
            buttonGrid->setIconSize(pixmap.rect().size());
            connect(buttonGrid, &QGridButton::rightClicked, this, std::bind(&Editor::updateGridButtonWithCursor, this, buttonGrid));
            mapGrid->addWidget(buttonGrid, i, j);
        }
    }
}

void Editor::updateGridButtonWithCursor(QGridButton *button) {

    QIcon icon(cursor().pixmap());
    updateGridButton(button, icon, "wood_wall");
}

QMenu* Editor::createGridButtonMenu(QGridButton *button) {
    QPixmap wood_pix("../client_src/resources/walls/brown_wall.png");
    QPixmap gray_pix("../client_src/resources/walls/gray_wall.jpg");
    QPixmap blue_pix("../client_src/resources/walls/blue_wall.png");
    QPixmap stone_pix("../client_src/resources/walls/stone_wall.png");
    QPixmap rpg_pix("../client_src/resources/items/rocket_launcher.png");
    QPixmap chain_pix("../client_src/resources/items/chain_cannon.png");
    QPixmap machine_pix("../client_src/resources/items/machine_gun.png");
    // QPixmap locked_pix("../client_src/resources/items/blood.png");
    // QPixmap barrel_pix("../client_src/resources/items/bullets.png");

    const char *wood_wall = "wood_wall";
    const char *gray_wall = "gray_wall";
    const char *blue_wall = "blue_wall";
    const char *stone_wall = "stone_wall";
    const char *rpg_gun = "rpg_gun";
    const char *chain_gun = "chain_gun";
    const char *machine_gun = "machine_gun";
    const char *locked_door = "locked_door";
    const char *barrel = "barrel";

    QIcon wood_icon(wood_pix);
    QIcon gray_icon(gray_pix);
    QIcon blue_icon(blue_pix);
    QIcon stone_icon(stone_pix);
    QIcon rpg_icon(rpg_pix);
    QIcon chain_icon(chain_pix);
    QIcon machine_icon(machine_pix);
    // QIcon locked_icon(locked_pix);
    // QIcon barrel_icon(barrel_pix);

    QMenu* menu = new QMenu();
    QAction* wood_action = menu->addAction(wood_icon, wood_wall);
    QAction* gray_action = menu->addAction(gray_icon, gray_wall);
    QAction* blue_action = menu->addAction(blue_icon, blue_wall);
    QAction* stone_action = menu->addAction(stone_icon, stone_wall);
    QAction* rpg_action = menu->addAction(rpg_icon, rpg_gun);
    QAction* chain_action = menu->addAction(chain_icon, chain_gun);
    QAction* machine_action = menu->addAction(machine_icon, machine_gun);
    //QAction* locked_action = menu->addAction(locked_icon, locked_door);
    //QAction* barrel_action = menu->addAction(barrel_icon, barrel);

    connect(wood_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, wood_icon, wood_wall));
    connect(gray_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, gray_icon, gray_wall));
    connect(blue_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, blue_icon, blue_wall));
    connect(stone_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, stone_icon, stone_wall));
    connect(rpg_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, rpg_icon, rpg_gun));
    connect(chain_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, chain_icon, chain_gun));
    connect(machine_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, machine_icon, machine_gun));
    //connect(locked_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, locked_icon, locked_door));
    //connect(barrel_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, barrel_icon, barrel));

    return menu;
}

void Editor::updateGridButton(QGridButton *button, QIcon &icon, const char *texture) {
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
    if (height.empty()) height = "15";
    if (width.empty()) width = "15";

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
            QGridButton* buttonGrid = qobject_cast<QGridButton*>(mapGrid->itemAtPosition(i, j)->widget());
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
            QGridButton* buttonGrid = new QGridButton();
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
    QPushButton* button_export = findChild<QPushButton*>("buttonExport");
    QPushButton* button_refresh = findChild<QPushButton*>("buttonRefresh");
    QPushButton* button_walls = findChild<QPushButton*>("buttonWalls");
    QPushButton* button_items = findChild<QPushButton*>("buttonItems");
    QPushButton* button_weapons = findChild<QPushButton*>("buttonWeapons");
    QPushButton* button_players = findChild<QPushButton*>("buttonPlayers");

    connect(button_export, &QPushButton::clicked,this, &Editor::exportMap);
    connect(button_refresh, &QPushButton::clicked,this, &Editor::refreshMapGrid);
    connect(button_walls, &QPushButton::clicked,this, std::bind(&Editor::updateTextureGrid, this, "walls"));
    connect(button_items, &QPushButton::clicked,this, std::bind(&Editor::updateTextureGrid, this, "items"));
    connect(button_weapons, &QPushButton::clicked,this, std::bind(&Editor::updateTextureGrid, this, "weapons"));
    connect(button_players, &QPushButton::clicked,this, std::bind(&Editor::updateTextureGrid, this, "players"));
}

void Editor::updateTextureGrid(std::string texture_type) {
    QGridLayout* textures_grid = findChild<QGridLayout*>("texturesGrid");
    QLayoutItem* item;
    while ((item = textures_grid->takeAt( 0)) != NULL){
        delete item->widget();
        delete item;
    }
    if (texture_type == "walls") renderWallsGrid(textures_grid);
    if (texture_type == "items") renderItemsGrid(textures_grid);
    if (texture_type == "weapons") renderWeaponsGrid(textures_grid);
    if (texture_type == "players") renderPlayersGrid(textures_grid);
}

void Editor::createTextureGrid() {
    renderWallsGrid(findChild<QGridLayout*>("texturesGrid"));
}

void Editor::renderWallsGrid(QGridLayout *texture_grid) {
    std::vector<QIcon> icons;

    QPixmap wood_pix("../client_src/resources/walls/brown_wall.png");
    QPixmap gray_pix("../client_src/resources/walls/gray_wall.jpg");
    QPixmap blue_pix("../client_src/resources//walls/blue_wall.png");
    QPixmap stone_pix("../client_src/resources//walls/stone_wall.png");
    // QPixmap locked_pix("../client_src/resources/items/blood.png");
    // QPixmap barrel_pix("../client_src/resources/items/bullets.png");

    icons.push_back(QIcon(wood_pix));
    icons.push_back(QIcon(gray_pix));
    icons.push_back(QIcon(blue_pix));
    icons.push_back(QIcon(stone_pix));
    // icons.push_back(QIcon(locked_pix));
    // icons.push_back(QIcon(barrel_pix));

    int i = 0;
    for (auto &icon: icons) {
        QGridButton* button = new QGridButton();
        button->setIcon(icon);
        button->setFlat(true);
        button->setIconSize(QSize(150, 150));
        connect(button, &QGridButton::clicked,this, std::bind(&Editor::changeCursor,this, icon.pixmap(35)));
        texture_grid->addWidget(button, 0, i);
        ++i;
    }
}

void Editor::changeCursor(QPixmap pix) {
    setCursor(QCursor(pix));
}

void Editor::renderItemsGrid(QGridLayout *texture_grid) {
    std::vector<QIcon> icons;

    QPixmap bullets_pix("../client_src/resources/items/bullets.png");
    QPixmap chest_pix("../client_src/resources/items/chest.png");
    QPixmap cross_pix("../client_src/resources/items/cross.png");
    QPixmap crown_pix("../client_src/resources/items/crown.png");
    QPixmap cup_pix("../client_src/resources/items/cup.png");
    QPixmap food_pix("../client_src/resources/items/food.png");
    QPixmap key_pix("../client_src/resources/items/key.png");
    QPixmap medic_pix("../client_src/resources/items/medical_kit.png");

    icons.push_back(QIcon(bullets_pix));
    icons.push_back(QIcon(chest_pix));
    icons.push_back(QIcon(cross_pix));
    icons.push_back(QIcon(crown_pix));
    icons.push_back(QIcon(cup_pix));
    icons.push_back(QIcon(food_pix));
    icons.push_back(QIcon(key_pix));
    icons.push_back(QIcon(medic_pix));

    int i = 0;
    for (auto &icon: icons) {
        QGridButton* button = new QGridButton();
        button->setIcon(icon);
        button->setFlat(true);
        button->setIconSize(QSize(150, 150));
        connect(button, &QGridButton::clicked,this, std::bind(&Editor::changeCursor,this, icon.pixmap(35)));
        texture_grid->addWidget(button, 0, i);
        ++i;
    }
}

void Editor::renderWeaponsGrid(QGridLayout *texture_grid) {
    std::vector<QIcon> icons;

    QPixmap rpg_pix("../client_src/resources/items/rocket_launcher.png");
    QPixmap chain_pix("../client_src/resources/items/chain_cannon.png");
    QPixmap machine_pix("../client_src/resources/items/machine_gun.png");

    icons.push_back(QIcon(rpg_pix));
    icons.push_back(QIcon(chain_pix));
    icons.push_back(QIcon(machine_pix));

    int i = 0;
    for (auto &icon: icons) {
        QGridButton* button = new QGridButton();
        button->setIcon(icon);
        button->setFlat(true);
        button->setIconSize(QSize(150, 150));
        connect(button, &QGridButton::clicked,this, std::bind(&Editor::changeCursor,this, icon.pixmap(35)));
        texture_grid->addWidget(button, 0, i);
        ++i;
    }
}

void Editor::renderPlayersGrid(QGridLayout *texture_grid) {

}

