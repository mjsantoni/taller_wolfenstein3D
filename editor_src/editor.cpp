#include <iostream>
#include <fstream>
#include <unordered_map>
#include <QDebug>
#include <QFileDialog>
#include "yaml-cpp/yaml.h"
#include "editor/editor.h"
#include "server/map_parser.h"
#include "ui_editor.h"
#include "editor/QGridButton.h"

#define DEF_HEIGHT 14
#define DEF_WIDTH 14


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

void Editor::dragEnterEvent(QDragEnterEvent *e){
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
    event->acceptProposedAction();
}

void Editor::dragLeaveEvent(QDragLeaveEvent* event) {
    event->accept();
}

void Editor::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton) {
        setCursor(Qt::ArrowCursor);
    }
}

void Editor::loadMap(std::string path) {
    if(path.empty()) path = getYamlPath();
    if (path.empty()) return;
    MapParser parser(path);
    std::vector<std::string> categories;
    QGridLayout* map_grid = findChild<QGridLayout*>("mapGrid");
    deleteWidgets(map_grid);
    std::pair<int, int> dimensions = parser.getDimensions();
    createButtonsMapGrid(map_grid, dimensions.first, dimensions.second, -1, -1);

    QPixmap wood_pix("../client_src/resources/walls/brown_wall.png");
    QPixmap gray_pix("../client_src/resources/walls/gray_wall.jpg");
    QPixmap blue_pix("../client_src/resources/walls/blue_wall.png");
    QPixmap stone_pix("../client_src/resources/walls/stone_wall.png");
    QPixmap rpg_pix("../client_src/resources/items/rocket_launcher.png");
    QPixmap chain_pix("../client_src/resources/items/chain_cannon.png");
    QPixmap machine_pix("../client_src/resources/items/machine_gun.png");
    QPixmap locked_pix("../client_src/resources/items/blood.png");
    QPixmap barrel_pix("../client_src/resources/items/bullets.png");
    QPixmap bullets_pix("../client_src/resources/items/bullets.png");
    QPixmap chest_pix("../client_src/resources/items/chest.png");
    QPixmap cross_pix("../client_src/resources/items/cross.png");
    QPixmap crown_pix("../client_src/resources/items/crown.png");
    QPixmap cup_pix("../client_src/resources/items/cup.png");
    QPixmap food_pix("../client_src/resources/items/food.png");
    QPixmap key_pix("../client_src/resources/items/key.png");
    QPixmap medic_pix("../client_src/resources/items/medical_kit.png");

    QIcon wood_icon(wood_pix);
    QIcon gray_icon(gray_pix);
    QIcon blue_icon(blue_pix);
    QIcon stone_icon(stone_pix);
    QIcon rpg_icon(rpg_pix);
    QIcon chain_icon(chain_pix);
    QIcon machine_icon(machine_pix);
    QIcon locked_icon(locked_pix);
    QIcon barrel_icon(barrel_pix);

    categories.push_back("scenarios");
    categories.push_back("items");
    categories.push_back("players");

    for(auto &category: categories){
        for(auto &items: parser.getCategory(category)){
            for(auto &positions: items.second){
                QGridButton* button = qobject_cast<QGridButton*>(map_grid->itemAtPosition(positions.first, positions.second)->widget());
                if (items.first == "wood_wall") updateGridButton(button, wood_icon, "wood_wall");
                if (items.first == "gray_wall") updateGridButton(button, QIcon(gray_pix), "gray_wall");
                if (items.first == "blue_wall") updateGridButton(button, QIcon(blue_pix), "blue_wall");
                if (items.first == "stone_wall") updateGridButton(button, QIcon(stone_pix), "stone_wall");
                if (items.first == "rpg_gun") updateGridButton(button, QIcon(rpg_pix), "rpg_gun");
                if (items.first == "chain_gun") updateGridButton(button, QIcon(chain_pix), "chain_gun");
                if (items.first == "machine_gun") updateGridButton(button, QIcon(machine_pix), "machine_gun");
                if (items.first == "locked_door") updateGridButton(button, QIcon(locked_pix), "locked_door");
                if (items.first == "barrel") updateGridButton(button, QIcon(barrel_pix), "barrel");
                if (items.first == "bullets") updateGridButton(button, QIcon(bullets_pix), "bullets");
                if (items.first == "chest") updateGridButton(button, QIcon(chest_pix), "chest");
                if (items.first == "cup") updateGridButton(button, QIcon(cup_pix), "cup");
                if (items.first == "cross") updateGridButton(button, QIcon(cross_pix), "cross");
                if (items.first == "crown") updateGridButton(button, QIcon(crown_pix), "crown");
                if (items.first == "food") updateGridButton(button, QIcon(food_pix), "food");
                if (items.first == "key") updateGridButton(button, QIcon(key_pix), "key");
                if (items.first == "medkit") updateGridButton(button, QIcon(medic_pix), "medkit");
            }
        }
    }
}


void Editor::createMapGrid() {
    QGridLayout* mapGrid = findChild<QGridLayout*>("mapGrid");
    QWidget* scrollAreaContent = new QWidget;
    scrollAreaContent->setStyleSheet("QWidget{background-color: black;}");
    scrollAreaContent->setLayout( mapGrid );
    QScrollArea* scrollArea = findChild<QScrollArea*>("scrollArea");
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(scrollAreaContent);
    createButtonsMapGrid(mapGrid, DEF_WIDTH, DEF_HEIGHT, -1, -1);
}

void Editor::updateGridButtonWithCursor(QGridButton *button) {
    QIcon icon(cursor().pixmap());
    updateGridButton(button, icon, currentCursor.c_str());
}

QMenu* Editor::createGridButtonMenu(QGridButton *button) {
    QPixmap wood_pix("../client_src/resources/walls/brown_wall.png");
    QPixmap gray_pix("../client_src/resources/walls/gray_wall.jpg");
    QPixmap blue_pix("../client_src/resources/walls/blue_wall.png");
    QPixmap stone_pix("../client_src/resources/walls/stone_wall.png");
    QPixmap rpg_pix("../client_src/resources/items/rocket_launcher.png");
    QPixmap chain_pix("../client_src/resources/items/chain_cannon.png");
    QPixmap machine_pix("../client_src/resources/items/machine_gun.png");
    QPixmap locked_pix("../client_src/resources/items/blood.png");
    QPixmap barrel_pix("../client_src/resources/items/bullets.png");
    QPixmap bullets_pix("../client_src/resources/items/bullets.png");
    QPixmap chest_pix("../client_src/resources/items/chest.png");
    QPixmap cross_pix("../client_src/resources/items/cross.png");
    QPixmap crown_pix("../client_src/resources/items/crown.png");
    QPixmap cup_pix("../client_src/resources/items/cup.png");
    QPixmap food_pix("../client_src/resources/items/food.png");
    QPixmap key_pix("../client_src/resources/items/key.png");
    QPixmap medic_pix("../client_src/resources/items/medical_kit.png");

    QIcon wood_icon(wood_pix);
    QIcon gray_icon(gray_pix);
    QIcon blue_icon(blue_pix);
    QIcon stone_icon(stone_pix);
    QIcon rpg_icon(rpg_pix);
    QIcon chain_icon(chain_pix);
    QIcon machine_icon(machine_pix);
    QIcon locked_icon(locked_pix);
    QIcon barrel_icon(barrel_pix);
    QIcon bullets_icon(bullets_pix);
    QIcon chest_icon(chest_pix);
    QIcon cross_icon(cross_pix);
    QIcon crown_icon(crown_pix);
    QIcon cup_icon(cup_pix);
    QIcon food_icon(food_pix);
    QIcon key_icon(key_pix);
    QIcon medic_icon(medic_pix);

    QMenu* menu = new QMenu();
    QMenu* menu_walls = new QMenu("Walls");
    QMenu* menu_weapons = new QMenu("Weapons");
    QMenu* menu_items = new QMenu("Items");

    menu_walls->setIcon(wood_icon);
    menu_weapons->setIcon(rpg_icon);
    menu_items->setIcon(medic_icon);

    QAction* wood_action = menu_walls->addAction(wood_icon, "Wood wall");
    QAction* gray_action = menu_walls->addAction(gray_icon, "Gray wall");
    QAction* blue_action = menu_walls->addAction(blue_icon, "Blue wall");
    QAction* stone_action = menu_walls->addAction(stone_icon, "Stone wall");
    QAction* locked_action = menu_walls->addAction(locked_icon, "Locked door");
    QAction* barrel_action = menu_walls->addAction(barrel_icon, "Barrel");
    QAction* rpg_action = menu_weapons->addAction(rpg_icon, "Rocket launcher");
    QAction* chain_action = menu_weapons->addAction(chain_icon, "Chain cannon");
    QAction* machine_action = menu_weapons->addAction(machine_icon, "Machine gun");
    QAction* bullets_action = menu_items->addAction(bullets_icon, "Bullets");
    QAction* chest_action = menu_items->addAction(chest_icon, "Chest");
    QAction* cross_action = menu_items->addAction(cross_icon, "Cross");
    QAction* crown_action = menu_items->addAction(crown_icon, "Crown");
    QAction* cup_action = menu_items->addAction(cup_icon, "Cup");
    QAction* food_action = menu_items->addAction(food_icon, "Food");
    QAction* key_action = menu_items->addAction(key_icon, "Key");
    QAction* medic_action = menu_items->addAction(medic_icon, "Medkit");

    menu->addMenu(menu_walls);
    menu->addMenu(menu_items);
    menu->addMenu(menu_weapons);

    connect(wood_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, wood_icon, "wood_wall"));
    connect(gray_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, gray_icon, "gray_wall"));
    connect(blue_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, blue_icon, "blue_wall"));
    connect(stone_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, stone_icon, "stone_wall"));
    connect(rpg_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, rpg_icon, "rpg_gun"));
    connect(chain_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, chain_icon, "chain_gun"));
    connect(machine_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, machine_icon, "machine_gun"));
    connect(locked_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, locked_icon, "locked_door"));
    connect(barrel_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, barrel_icon, "barrel"));
    connect(bullets_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, bullets_icon, "bullets"));
    connect(chest_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, chest_icon, "chest"));
    connect(cross_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, cross_icon, "cross"));
    connect(crown_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, crown_icon, "crown"));
    connect(cup_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, cup_icon, "cup"));
    connect(food_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, food_icon, "food"));
    connect(key_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, key_icon, "key"));
    connect(medic_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, medic_icon, "medkit"));

    return menu;
}

void Editor::updateGridButton(QGridButton *button, QIcon icon, const char *texture) {
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
    if (height.empty()) height = "14";
    if (width.empty()) width = "14";

    std::vector<std::pair<int, int>> wood_positions;
    std::vector<std::pair<int, int>> gray_positions;
    std::vector<std::pair<int, int>> stone_positions;
    std::vector<std::pair<int, int>> blue_positions;
    std::vector<std::pair<int, int>> rpg_positions;
    std::vector<std::pair<int, int>> chain_positions;
    std::vector<std::pair<int, int>> machine_positions;
    std::vector<std::pair<int, int>> bullets_positions;
    std::vector<std::pair<int, int>> chest_positions;
    std::vector<std::pair<int, int>> cup_positions;
    std::vector<std::pair<int, int>> cross_positions;
    std::vector<std::pair<int, int>> crown_positions;
    std::vector<std::pair<int, int>> food_positions;
    std::vector<std::pair<int, int>> key_positions;
    std::vector<std::pair<int, int>> medkit_positions;
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
            if (variantTexture == "gray_wall") gray_positions.emplace_back(i, j);
            if (variantTexture == "rpg_gun") rpg_positions.emplace_back(i, j);
            if (variantTexture == "chain_gun") chain_positions.emplace_back(i, j);
            if (variantTexture == "machine_gun") machine_positions.emplace_back(i, j);
            if (variantTexture == "bullets") bullets_positions.emplace_back(i, j);
            if (variantTexture == "chest") chest_positions.emplace_back(i, j);
            if (variantTexture == "cup") cup_positions.emplace_back(i, j);
            if (variantTexture == "cross") cross_positions.emplace_back(i, j);
            if (variantTexture == "crown") crown_positions.emplace_back(i, j);
            if (variantTexture == "food") food_positions.emplace_back(i, j);
            if (variantTexture == "key") key_positions.emplace_back(i, j);
            if (variantTexture == "medkit") medkit_positions.emplace_back(i, j);
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
    out << YAML::Key << "gray_wall";
    out << YAML::Value << gray_positions << YAML::EndSeq;
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
    out << YAML::Key << "bullets";
    out << YAML::Value << bullets_positions << YAML::EndSeq;
    out << YAML::Key << "chest";
    out << YAML::Value << chest_positions << YAML::EndSeq;
    out << YAML::Key << "cross";
    out << YAML::Value << cross_positions << YAML::EndSeq;
    out << YAML::Key << "crown";
    out << YAML::Value << crown_positions << YAML::EndSeq;
    out << YAML::Key << "cup";
    out << YAML::Value << cup_positions << YAML::EndSeq;
    out << YAML::Key << "food";
    out << YAML::Value << food_positions << YAML::EndSeq;
    out << YAML::Key << "key";
    out << YAML::Value << key_positions << YAML::EndSeq;
    out << YAML::Key << "medkit";
    out << YAML::Value << medkit_positions << YAML::EndSeq;
    out << YAML::EndMap;

    out << YAML::Key << "players";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "0";
    out << YAML::Value << YAML::Flow << YAML::BeginSeq << Coordinate(1, 2) << Coordinate(3, 4) << Coordinate(5, 6) << YAML::EndSeq;
    out << YAML::Key << "1";
    out << YAML::Value << YAML::Flow << YAML::BeginSeq << Coordinate(2, 4) << Coordinate(5, 0) << Coordinate(6, 6) << YAML::EndSeq;
    out << YAML::EndMap;

    out << YAML::EndMap;

    std::string savePath = saveYamlPath();
    if (savePath.empty()) return;
    std::fstream file(savePath, std::ios::out);
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

    createButtonsMapGrid(mapGrid, rows, cols, gridRows, gridCols);

     // TODO Agregar sacar celdas
}

void Editor::createButtonsMapGrid(QGridLayout* mapGrid, int rows, int cols, int gridRows, int gridCols) {
    QPixmap pixmap("../client_src/resources/empty.jpg");
    QIcon buttonIcon(pixmap);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i < gridRows && j < gridCols) continue;
            QGridButton* buttonGrid = new QGridButton();
            buttonGrid->setStyleSheet("QGridButton::menu-indicator{width:0px;}");
            buttonGrid->setMaximumSize(70, 70);
            buttonGrid->setMinimumSize(50,50);
            buttonGrid->setIcon(buttonIcon);
            buttonGrid->setIconSize(pixmap.rect().size());
            QMenu* menu = createGridButtonMenu(buttonGrid);
            buttonGrid->setMenu(menu);
            connect(buttonGrid, &QGridButton::rightClicked, this, std::bind(&Editor::updateGridButtonWithCursor, this, buttonGrid));
            mapGrid->addWidget(buttonGrid, i, j);
        }
    }
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
    deleteWidgets(textures_grid);
    if (texture_type == "walls") renderWallsGrid(textures_grid);
    if (texture_type == "items") renderItemsGrid(textures_grid);
    if (texture_type == "weapons") renderWeaponsGrid(textures_grid);
    if (texture_type == "players") renderPlayersGrid(textures_grid);
}

void Editor::createTextureGrid() {
    renderWallsGrid(findChild<QGridLayout*>("texturesGrid"));
}

void Editor::renderWallsGrid(QGridLayout *texture_grid) {
    std::vector<std::pair<QIcon, std::string>> icons;


    QPixmap wood_pix("../client_src/resources/walls/brown_wall.png");
    QPixmap gray_pix("../client_src/resources/walls/gray_wall.jpg");
    QPixmap blue_pix("../client_src/resources//walls/blue_wall.png");
    QPixmap stone_pix("../client_src/resources//walls/stone_wall.png");
    // QPixmap locked_pix("../client_src/resources/items/blood.png");
    // QPixmap barrel_pix("../client_src/resources/items/bullets.png");

    icons.emplace_back(QIcon(wood_pix), "wood_wall");
    icons.emplace_back(QIcon(gray_pix), "gray_wall");
    icons.emplace_back(QIcon(blue_pix), "blue_wall");
    icons.emplace_back(QIcon(stone_pix), "stone_wall");
    // icons.push_back(QIcon(locked_pix));
    // icons.push_back(QIcon(barrel_pix));

    renderTextureGrid(texture_grid, icons);
}

void Editor::changeCursor(QPixmap pix, std::string texture_name) {
    setCursor(QCursor(pix));
    currentCursor = texture_name;
}

void Editor::renderItemsGrid(QGridLayout *texture_grid) {
    std::vector<std::pair<QIcon, std::string>> icons;

    QPixmap bullets_pix("../client_src/resources/items/bullets.png");
    QPixmap chest_pix("../client_src/resources/items/chest.png");
    QPixmap cross_pix("../client_src/resources/items/cross.png");
    QPixmap crown_pix("../client_src/resources/items/crown.png");
    QPixmap cup_pix("../client_src/resources/items/cup.png");
    QPixmap food_pix("../client_src/resources/items/food.png");
    QPixmap key_pix("../client_src/resources/items/key.png");
    QPixmap medic_pix("../client_src/resources/items/medical_kit.png");

    icons.emplace_back(QIcon(bullets_pix), "bullets");
    icons.emplace_back(QIcon(chest_pix), "chest");
    icons.emplace_back(QIcon(cross_pix), "cross");
    icons.emplace_back(QIcon(crown_pix), "crown");
    icons.emplace_back(QIcon(cup_pix), "cup");
    icons.emplace_back(QIcon(food_pix), "food");
    icons.emplace_back(QIcon(key_pix), "key");
    icons.emplace_back(QIcon(medic_pix), "medkit");

    renderTextureGrid(texture_grid, icons);
}

void Editor::renderWeaponsGrid(QGridLayout *texture_grid) {
    std::vector<std::pair<QIcon, std::string>> icons;

    QPixmap rpg_pix("../client_src/resources/items/rocket_launcher.png");
    QPixmap chain_pix("../client_src/resources/items/chain_cannon.png");
    QPixmap machine_pix("../client_src/resources/items/machine_gun.png");

    icons.emplace_back(QIcon(rpg_pix), "rpg_gun");
    icons.emplace_back(QIcon(chain_pix), "chain_gun");
    icons.emplace_back(QIcon(machine_pix), "machine_gun");

    renderTextureGrid(texture_grid, icons);
}

void Editor::renderPlayersGrid(QGridLayout *texture_grid) {

}

void Editor::renderTextureGrid(QGridLayout *texture_grid, std::vector<std::pair<QIcon, std::string>> icons) {
    int i = 0;
    int j = 0;
    for (auto &icon: icons) {
        QPushButton* button = new QPushButton();
        button->setIcon(icon.first);
        button->setFlat(true);
        button->setIconSize(QSize(125, 125));
        connect(button, &QPushButton::clicked,this, std::bind(&Editor::changeCursor,this, icon.first.pixmap(35), icon.second));
        texture_grid->addWidget(button, j, i);
        ++i;
        if (i % 4 == 0) {
            ++j;
            i = 0;
        }
    }
}

void Editor::deleteWidgets(QGridLayout *layout) {
    QLayoutItem* item;
    while ((item = layout->takeAt( 0)) != NULL){
        delete item->widget();
        delete item;
    }
}

