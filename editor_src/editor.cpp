#include "editor/editor.h"

#define DEF_HEIGHT 14
#define DEF_WIDTH 14
#define MAX_PLAYERS 8
#define CURSOR_SIZE 50


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
    Coordinate dimensions = parser.getDimensions();
    createButtonsMapGrid(map_grid, dimensions.x, dimensions.y, -1, -1);
    QPixmap wood_pix("../editor_src/resources/walls/brown_wall.png");
    QPixmap rock_pix("../editor_src/resources/walls/rock_wall.jpg");
    QPixmap blue_pix("../editor_src/resources/walls/blue_wall.png");
    QPixmap stone_pix("../editor_src/resources/walls/stone_wall.png");
    QPixmap rpg_pix("../editor_src/resources/items/rocket_launcher.png");
    QPixmap chain_pix("../editor_src/resources/items/chain_cannon.png");
    QPixmap machine_pix("../editor_src/resources/items/machine_gun.png");
    QPixmap locked_pix("../editor_src/resources/walls/silver_door.png");
    QPixmap barrel_pix("../editor_src/resources/misc/barrel.png");
    QPixmap table_pix("../editor_src/resources/misc/table.png");
    QPixmap bullets_pix("../editor_src/resources/items/bullets.png");
    QPixmap chest_pix("../editor_src/resources/items/chest.png");
    QPixmap cross_pix("../editor_src/resources/items/cross.png");
    QPixmap crown_pix("../editor_src/resources/items/crown.png");
    QPixmap goblet_pix("../editor_src/resources/items/goblet.png");
    QPixmap food_pix("../editor_src/resources/items/food.png");
    QPixmap key_pix("../editor_src/resources/items/key.png");
    QPixmap medic_pix("../editor_src/resources/items/medical_kit.png");
    QPixmap water_pix("../editor_src/resources/items/water_puddle.png");
    QPixmap player_pix("../editor_src/resources/player.png");

    categories.push_back("scenarios");
    categories.push_back("items");
    categories.push_back("players");

    for(auto &category: categories){
        for(auto &items: parser.getCategory(category)){
            for(auto &positions: items.second){
                QGridButton* button = qobject_cast<QGridButton*>(map_grid->itemAtPosition(positions.x, positions.y)->widget());
                if (items.first == "wood_wall") updateGridButton(button, QIcon(wood_pix), "wood_wall");
                else if (items.first == "rock_wall") updateGridButton(button, QIcon(rock_pix), "rock_wall");
                else if (items.first == "blue_wall") updateGridButton(button, QIcon(blue_pix), "blue_wall");
                else if (items.first == "stone_wall") updateGridButton(button, QIcon(stone_pix), "stone_wall");
                else if (items.first == "rpg_gun") updateGridButton(button, QIcon(rpg_pix), "rpg_gun");
                else if (items.first == "chain_gun") updateGridButton(button, QIcon(chain_pix), "chain_gun");
                else if (items.first == "machine_gun") updateGridButton(button, QIcon(machine_pix), "machine_gun");
                else if (items.first == "locked_door") updateGridButton(button, QIcon(locked_pix), "locked_door");
                else if (items.first == "barrel") updateGridButton(button, QIcon(barrel_pix), "barrel");
                else if (items.first == "table") updateGridButton(button, QIcon(table_pix), "table");
                else if (items.first == "bullets") updateGridButton(button, QIcon(bullets_pix), "bullets");
                else if (items.first == "chest") updateGridButton(button, QIcon(chest_pix), "chest");
                else if (items.first == "goblet") updateGridButton(button, QIcon(goblet_pix), "goblet");
                else if (items.first == "cross") updateGridButton(button, QIcon(cross_pix), "cross");
                else if (items.first == "crown") updateGridButton(button, QIcon(crown_pix), "crown");
                else if (items.first == "food") updateGridButton(button, QIcon(food_pix), "food");
                else if (items.first == "key") updateGridButton(button, QIcon(key_pix), "key");
                else if (items.first == "medkit") updateGridButton(button, QIcon(medic_pix), "medkit");
                else if (items.first == "water_puddle") updateGridButton(button, QIcon(water_pix), "water_puddle");
                else if (items.first.length() == 1) updateGridButton(button, QIcon(player_pix), "player");
            }
        }
    }
}


void Editor::createMapGrid() {
    QGridLayout* mapGrid = findChild<QGridLayout*>("mapGrid");
    QWidget* scrollAreaContent = new QWidget;
    scrollAreaContent->setStyleSheet("QWidget{background-color: #29172B;}");
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
    QPixmap wood_pix("../editor_src/resources/walls/brown_wall.png");
    QPixmap rock_pix("../editor_src/resources/walls/rock_wall.jpg");
    QPixmap blue_pix("../editor_src/resources/walls/blue_wall.png");
    QPixmap stone_pix("../editor_src/resources/walls/stone_wall.png");
    QPixmap rpg_pix("../editor_src/resources/items/rocket_launcher.png");
    QPixmap chain_pix("../editor_src/resources/items/chain_cannon.png");
    QPixmap machine_pix("../editor_src/resources/items/machine_gun.png");
    QPixmap locked_pix("../editor_src/resources/walls/silver_door.png");
    QPixmap barrel_pix("../editor_src/resources/misc/barrel.png");
    QPixmap table_pix("../editor_src/resources/misc/table.png");
    QPixmap bullets_pix("../editor_src/resources/items/bullets.png");
    QPixmap chest_pix("../editor_src/resources/items/chest.png");
    QPixmap cross_pix("../editor_src/resources/items/cross.png");
    QPixmap crown_pix("../editor_src/resources/items/crown.png");
    QPixmap goblet_pix("../editor_src/resources/items/goblet.png");
    QPixmap food_pix("../editor_src/resources/items/food.png");
    QPixmap key_pix("../editor_src/resources/items/key.png");
    QPixmap medic_pix("../editor_src/resources/items/medical_kit.png");
    QPixmap water_pix("../editor_src/resources/items/water_puddle.png");

    QIcon wood_icon(wood_pix);
    QIcon rock_icon(rock_pix);
    QIcon blue_icon(blue_pix);
    QIcon stone_icon(stone_pix);
    QIcon rpg_icon(rpg_pix);
    QIcon chain_icon(chain_pix);
    QIcon machine_icon(machine_pix);
    QIcon locked_icon(locked_pix);
    QIcon barrel_icon(barrel_pix);
    QIcon table_icon(table_pix);
    QIcon bullets_icon(bullets_pix);
    QIcon chest_icon(chest_pix);
    QIcon cross_icon(cross_pix);
    QIcon crown_icon(crown_pix);
    QIcon goblet_icon(goblet_pix);
    QIcon food_icon(food_pix);
    QIcon key_icon(key_pix);
    QIcon medic_icon(medic_pix);
    QIcon water_icon(water_pix);

    QMenu* menu = new QMenu();
    QMenu* menu_walls = new QMenu("Walls");
    QMenu* menu_weapons = new QMenu("Weapons");
    QMenu* menu_items = new QMenu("Items");

    menu_walls->setIcon(wood_icon);
    menu_weapons->setIcon(rpg_icon);
    menu_items->setIcon(medic_icon);

    QAction* wood_action = menu_walls->addAction(wood_icon, "Wood wall");
    QAction* rock_action = menu_walls->addAction(rock_icon, "Gray wall");
    QAction* blue_action = menu_walls->addAction(blue_icon, "Blue wall");
    QAction* stone_action = menu_walls->addAction(stone_icon, "Stone wall");
    QAction* locked_action = menu_walls->addAction(locked_icon, "Locked door");
    QAction* barrel_action = menu_walls->addAction(barrel_icon, "Barrel");
    QAction* table_action = menu_items->addAction(table_icon, "Table");
    QAction* rpg_action = menu_weapons->addAction(rpg_icon, "Rocket launcher");
    QAction* chain_action = menu_weapons->addAction(chain_icon, "Chain cannon");
    QAction* machine_action = menu_weapons->addAction(machine_icon, "Machine gun");
    QAction* bullets_action = menu_items->addAction(bullets_icon, "Bullets");
    QAction* chest_action = menu_items->addAction(chest_icon, "Chest");
    QAction* cross_action = menu_items->addAction(cross_icon, "Cross");
    QAction* crown_action = menu_items->addAction(crown_icon, "Crown");
    QAction* goblet_action = menu_items->addAction(goblet_icon, "Cup");
    QAction* food_action = menu_items->addAction(food_icon, "Food");
    QAction* key_action = menu_items->addAction(key_icon, "Key");
    QAction* medic_action = menu_items->addAction(medic_icon, "Medkit");
    QAction* water_action = menu_items->addAction(water_icon, "Water puddle");

    menu->addMenu(menu_walls);
    menu->addMenu(menu_items);
    menu->addMenu(menu_weapons);

    connect(wood_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, wood_icon, "wood_wall"));
    connect(rock_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, rock_icon, "stone_wall"));
    connect(blue_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, blue_icon, "blue_wall"));
    connect(stone_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, stone_icon, "stone_wall"));
    connect(rpg_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, rpg_icon, "rpg_gun"));
    connect(chain_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, chain_icon, "chain_gun"));
    connect(machine_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, machine_icon, "machine_gun"));
    connect(locked_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, locked_icon, "locked_door"));
    connect(barrel_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, barrel_icon, "barrel"));
    connect(table_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, table_icon, "table"));
    connect(bullets_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, bullets_icon, "bullets"));
    connect(chest_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, chest_icon, "chest"));
    connect(cross_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, cross_icon, "cross"));
    connect(crown_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, crown_icon, "crown"));
    connect(goblet_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, goblet_icon, "goblet"));
    connect(food_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, food_icon, "food"));
    connect(key_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, key_icon, "key"));
    connect(medic_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, medic_icon, "medkit"));
    connect(water_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, water_icon, "water_puddle"));

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
    /* Height and weapon_width input */
    QLineEdit* inputHeight = findChild<QLineEdit*>("inputHeight");
    QLineEdit* inputWidth = findChild<QLineEdit*>("inputWidth");
    QString qHeight= QString("%1").arg(inputHeight->text());
    QString qWidth = QString("%1").arg(inputWidth->text());
    std::string height = qHeight.toStdString();
    std::string width = qWidth.toStdString();
    if (height.empty()) height = "14";
    if (width.empty()) width = "14";

    std::vector<std::pair<int, int>> wood_positions;
    std::vector<std::pair<int, int>> rock_positions;
    std::vector<std::pair<int, int>> stone_positions;
    std::vector<std::pair<int, int>> blue_positions;
    std::vector<std::pair<int, int>> rpg_positions;
    std::vector<std::pair<int, int>> chain_positions;
    std::vector<std::pair<int, int>> machine_positions;
    std::vector<std::pair<int, int>> bullets_positions;
    std::vector<std::pair<int, int>> chest_positions;
    std::vector<std::pair<int, int>> goblet_positions;
    std::vector<std::pair<int, int>> cross_positions;
    std::vector<std::pair<int, int>> crown_positions;
    std::vector<std::pair<int, int>> food_positions;
    std::vector<std::pair<int, int>> key_positions;
    std::vector<std::pair<int, int>> medkit_positions;
    std::vector<std::pair<int, int>> locked_positions;
    std::vector<std::pair<int, int>> barrel_positions;
    std::vector<std::pair<int, int>> table_positions;
    std::vector<std::pair<int, int>> water_positions;
    std::vector<std::pair<int, int>> player_positions;

    /* Map input */
    QGridLayout* mapGrid = findChild<QGridLayout*>("mapGrid");
    for (int i = 0; i < mapGrid->rowCount(); ++i) {
        for (int j = 0; j < mapGrid->columnCount(); ++j) {
            QGridButton* buttonGrid = qobject_cast<QGridButton*>(mapGrid->itemAtPosition(i, j)->widget());
            std::string variantTexture = buttonGrid->property("texture").toString().toStdString();
            if (variantTexture == "wood_wall") wood_positions.emplace_back(i, j);
            if (variantTexture == "stone_wall") stone_positions.emplace_back(i, j);
            if (variantTexture == "blue_wall") blue_positions.emplace_back(i, j);
            if (variantTexture == "rock_wall") rock_positions.emplace_back(i, j);
            if (variantTexture == "rpg_gun") rpg_positions.emplace_back(i, j);
            if (variantTexture == "chain_gun") chain_positions.emplace_back(i, j);
            if (variantTexture == "machine_gun") machine_positions.emplace_back(i, j);
            if (variantTexture == "bullets") bullets_positions.emplace_back(i, j);
            if (variantTexture == "chest") chest_positions.emplace_back(i, j);
            if (variantTexture == "goblet") goblet_positions.emplace_back(i, j);
            if (variantTexture == "cross") cross_positions.emplace_back(i, j);
            if (variantTexture == "crown") crown_positions.emplace_back(i, j);
            if (variantTexture == "food") food_positions.emplace_back(i, j);
            if (variantTexture == "key") key_positions.emplace_back(i, j);
            if (variantTexture == "medkit") medkit_positions.emplace_back(i, j);
            if (variantTexture == "locked_door") locked_positions.emplace_back(i, j);
            if (variantTexture == "barrel") barrel_positions.emplace_back(i, j);
            if (variantTexture == "table") table_positions.emplace_back(i, j);
            if (variantTexture == "water_puddle") water_positions.emplace_back(i, j);
            if (variantTexture == "player") player_positions.emplace_back(i, j);
        }
    }

    YAML::Emitter out;
    out << YAML::BeginMap;

    out << YAML::Key << "dimensions";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "weapon_width" << YAML::Value << width;
    out << YAML::Key << "height" << YAML::Value << height;
    out << YAML::EndMap;

    out << YAML::Key << "scenarios";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "wood_wall";
    out << YAML::Value << wood_positions << YAML::EndSeq;
    out << YAML::Key << "rock_wall";
    out << YAML::Value << rock_positions << YAML::EndSeq;
    out << YAML::Key << "stone_wall";
    out << YAML::Value << stone_positions << YAML::EndSeq;
    out << YAML::Key << "blue_wall";
    out << YAML::Value << blue_positions << YAML::EndSeq;
    out << YAML::Key << "barrel";
    out << YAML::Value << barrel_positions << YAML::EndSeq;
    out << YAML::Key << "locked_door";
    out << YAML::Value << locked_positions << YAML::EndSeq;
    out << YAML::Key << "table";
    out << YAML::Value << table_positions << YAML::EndSeq;
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
    out << YAML::Key << "goblet";
    out << YAML::Value << goblet_positions << YAML::EndSeq;
    out << YAML::Key << "food";
    out << YAML::Value << food_positions << YAML::EndSeq;
    out << YAML::Key << "key";
    out << YAML::Value << key_positions << YAML::EndSeq;
    out << YAML::Key << "medkit";
    out << YAML::Value << medkit_positions << YAML::EndSeq;
    out << YAML::Key << "water_puddle";
    out << YAML::Value << water_positions << YAML::EndSeq;
    out << YAML::EndMap;

    out << YAML::Key << "players";
    out << YAML::Value << YAML::BeginMap;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        out << YAML::Key << std::to_string(i);
        out << YAML::Value << YAML::Flow << YAML::BeginSeq << player_positions[i] << YAML::EndSeq;
    }
    out << YAML::EndMap;

    out << YAML::EndMap;

    std::string savePath = saveYamlPath();
    if (savePath.empty()) return;
    std::fstream file(savePath, std::ios::out);
    file << out.c_str();
    file.close();
}

void Editor::refreshMapGrid(){
    /* Height and weapon_width input */
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
    QPixmap pixmap("../editor_src/resources/empty.jpg");
    QIcon buttonIcon(pixmap);


    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i < gridRows && j < gridCols) continue;
            QGridButton* buttonGrid = new QGridButton();
            buttonGrid->setStyleSheet("QGridButton::menu-indicator{weapon_width:0px;}");
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
    QPushButton* button_scenario = findChild<QPushButton*>("buttonScenario");
    QPushButton* button_items = findChild<QPushButton*>("buttonItems");
    QPushButton* button_weapons = findChild<QPushButton*>("buttonWeapons");
    QPushButton* button_players = findChild<QPushButton*>("buttonPlayers");

    connect(button_export, &QPushButton::clicked,this, &Editor::exportMap);
    connect(button_refresh, &QPushButton::clicked,this, &Editor::refreshMapGrid);
    connect(button_scenario, &QPushButton::clicked,this, std::bind(&Editor::updateTextureGrid, this, "walls"));
    connect(button_items, &QPushButton::clicked,this, std::bind(&Editor::updateTextureGrid, this, "items"));
    connect(button_weapons, &QPushButton::clicked,this, std::bind(&Editor::updateTextureGrid, this, "weapons"));
    connect(button_players, &QPushButton::clicked,this, std::bind(&Editor::updateTextureGrid, this, "players"));
}

void Editor::updateTextureGrid(std::string texture_type) {
    QGridLayout* textures_grid = findChild<QGridLayout*>("texturesGrid");
    deleteWidgets(textures_grid);
    if (texture_type == "walls") renderScenarioGrid(textures_grid);
    if (texture_type == "items") renderItemsGrid(textures_grid);
    if (texture_type == "weapons") renderWeaponsGrid(textures_grid);
    if (texture_type == "players") renderPlayersGrid(textures_grid);
}

void Editor::createTextureGrid() {
    renderScenarioGrid(findChild<QGridLayout*>("texturesGrid"));
}

void Editor::renderScenarioGrid(QGridLayout *texture_grid) {
    std::vector<std::pair<QIcon, std::string>> icons;

    QPixmap wood_pix("../editor_src/resources/walls/brown_wall.png");
    QPixmap rock_pix("../editor_src/resources/walls/rock_wall.jpg");
    QPixmap blue_pix("../editor_src/resources//walls/blue_wall.png");
    QPixmap stone_pix("../editor_src/resources//walls/stone_wall.png");
    QPixmap locked_pix("../editor_src/resources/walls/silver_door.png");
    QPixmap barrel_pix("../editor_src/resources/misc/barrel.png");
    QPixmap table_pix("../editor_src/resources/misc/table.png");
    QPixmap water_pix("../editor_src/resources/items/water_puddle.png");

    icons.emplace_back(QIcon(wood_pix), "wood_wall");
    icons.emplace_back(QIcon(rock_pix), "stone_wall");
    icons.emplace_back(QIcon(blue_pix), "blue_wall");
    icons.emplace_back(QIcon(stone_pix), "stone_wall");
    icons.emplace_back(QIcon(locked_pix), "locked_door");
    icons.emplace_back(QIcon(barrel_pix), "barrel");
    icons.emplace_back(QIcon(table_pix), "table");
    icons.emplace_back(QIcon(water_pix), "water_puddle");

    renderTextureGrid(texture_grid, icons);
}

void Editor::changeCursor(QPixmap pix, std::string texture_name) {
    setCursor(QCursor(pix));
    currentCursor = texture_name;
}

void Editor::renderItemsGrid(QGridLayout *texture_grid) {
    std::vector<std::pair<QIcon, std::string>> icons;

    QPixmap bullets_pix("../editor_src/resources/items/bullets.png");
    QPixmap chest_pix("../editor_src/resources/items/chest.png");
    QPixmap cross_pix("../editor_src/resources/items/cross.png");
    QPixmap crown_pix("../editor_src/resources/items/crown.png");
    QPixmap goblet_pix("../editor_src/resources/items/goblet.png");
    QPixmap food_pix("../editor_src/resources/items/food.png");
    QPixmap key_pix("../editor_src/resources/items/key.png");
    QPixmap medic_pix("../editor_src/resources/items/medical_kit.png");

    icons.emplace_back(QIcon(bullets_pix), "bullets");
    icons.emplace_back(QIcon(chest_pix), "chest");
    icons.emplace_back(QIcon(cross_pix), "cross");
    icons.emplace_back(QIcon(crown_pix), "crown");
    icons.emplace_back(QIcon(goblet_pix), "goblet");
    icons.emplace_back(QIcon(food_pix), "food");
    icons.emplace_back(QIcon(key_pix), "key");
    icons.emplace_back(QIcon(medic_pix), "medkit");

    renderTextureGrid(texture_grid, icons);
}

void Editor::renderWeaponsGrid(QGridLayout *texture_grid) {
    std::vector<std::pair<QIcon, std::string>> icons;

    QPixmap rpg_pix("../editor_src/resources/items/rocket_launcher.png");
    QPixmap chain_pix("../editor_src/resources/items/chain_cannon.png");
    QPixmap machine_pix("../editor_src/resources/items/machine_gun.png");

    icons.emplace_back(QIcon(rpg_pix), "rpg_gun");
    icons.emplace_back(QIcon(chain_pix), "chain_gun");
    icons.emplace_back(QIcon(machine_pix), "machine_gun");

    renderTextureGrid(texture_grid, icons);
}

void Editor::renderPlayersGrid(QGridLayout *texture_grid) {
    std::vector<std::pair<QIcon, std::string>> icons;

    QPixmap player_pix("../editor_src/resources/player.png");

    icons.emplace_back(QIcon(player_pix), "player");

    renderTextureGrid(texture_grid, icons);
}

void Editor::renderTextureGrid(QGridLayout *texture_grid, std::vector<std::pair<QIcon, std::string>> icons) {
    int i = 0;
    int j = 0;
    for (auto &icon: icons) {
        QPushButton* button = new QPushButton();
        button->setIcon(icon.first);
        button->setFlat(true);
        button->setIconSize(QSize(125, 125));
        connect(button, &QPushButton::clicked,this, std::bind(&Editor::changeCursor,this, icon.first.pixmap(CURSOR_SIZE), icon.second));
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

