#include "editor/editor.h"

#define DEF_HEIGHT 14
#define DEF_WIDTH 14
#define CURSOR_SIZE 50
#define TEXTURES_GRID_WIDTH 4
#define BUTTON_MAXIMUM_SIZE 70
#define BUTTON_MINIMUM_SIZE 50

#define EMPTY_PATH "../editor_src/resources/empty.png"
#define WOOD_WALL_PATH "../editor_src/resources/walls/brown_wall.png"
#define ROCK_WALL_PATH "../editor_src/resources/walls/rock_wall.jpg"
#define LOCKED_DOOR_PATH "../client_src/resources/walls/locked_door.png"
#define UNLOCKED_DOOR_PATH "../client_src/resources/walls/unlocked_door.png"
#define FAKE_WALL_PATH "../client_src/resources/walls/fake_wall.png"
#define BLUE_WALL_PATH  "../editor_src/resources/walls/blue_wall.png"
#define STONE_WALL_PATH "../editor_src/resources/walls/stone_wall.png"
#define RPG_PATH "../editor_src/resources/items/rocket_launcher.png"
#define MACHINE_GUN_PATH "../editor_src/resources/items/machine_gun.png"
#define CHAIN_GUN_PATH "../editor_src/resources/items/chain_cannon.png"
#define BARREL_PATH  "../editor_src/resources/misc/barrel.png"
#define TABLE_PATH "../editor_src/resources/misc/table.png"
#define BULLETS_PATH "../editor_src/resources/items/bullets.png"
#define CHEST_PATH "../editor_src/resources/items/chest.png"
#define CROSS_PATH "../editor_src/resources/items/cross.png"
#define CROWN_PATH "../editor_src/resources/items/crown.png"
#define GOBLET_PATH "../editor_src/resources/items/goblet.png"
#define FOOD_PATH "../editor_src/resources/items/food.png"
#define KEY_PATH "../editor_src/resources/items/key.png"
#define MEDKIT_PATH "../editor_src/resources/items/medical_kit.png"
#define WATER_PATH "../editor_src/resources/items/water_puddle.png"
#define PLAYER_PATH "../editor_src/resources/player.png"

#define WOOD_WALL_STRING "wood_wall"
#define STONE_WALL_STRING "stone_wall"
#define BLUE_WALL_STRING "blue_wall"
#define ROCK_WALL_STRING "rock_wall"
#define RPG_STRING "rpg_gun"
#define CHAIN_STRING "chain_gun"
#define MACHINE_STRING "machine_gun"
#define BULLETS_STRING "bullets"
#define CHEST_STRING "chest"
#define GOBLET_STRING "goblet"
#define CROSS_STRING "cross"
#define CROWN_STRING "crown"
#define FOOD_STRING "food"
#define KEY_STRING "key"
#define MEDKIT_STRING "medkit"
#define LOCKED_STRING "locked_door"
#define UNLOCKED_STRING "unlocked_door"
#define FAKE_WALL_STRING "fake_wall"
#define BARREL_STRING "barrel"
#define TABLE_STRING "table"
#define WATER_STRING "water_puddle"
#define PLAYER_STRING "player"


Editor::Editor(QMainWindow* parent) : QMainWindow(parent) {
  Ui::Editor editor;
  editor.setupUi(this);
  setAcceptDrops(true);
  auto* load = new QAction("Load map", this);
  auto* save = new QAction("Save Map", this);
  auto* quit = new QAction("Quit", this);
  save->setShortcuts(QKeySequence::Save);
  load->setShortcuts(QKeySequence::Open);
  quit->setShortcuts(QKeySequence::Quit);
  QMenu* file = menuBar()->addMenu("File");
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

void Editor::dragEnterEvent(QDragEnterEvent* e) {
  if (e->mimeData()->hasUrls()) {
    e->acceptProposedAction();
  }
}

void Editor::dropEvent(QDropEvent* e) {
  const QMimeData* mimeData = e->mimeData();
      foreach (const QUrl& url, mimeData->urls()) {
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

void Editor::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    setCursor(Qt::ArrowCursor);
    currentCursor = "empty";
  }
}

void Editor::loadMap(std::string path) {
  if (path.empty()) path = getYamlPath();
  if (path.empty()) return;
  MapParser parser(path);
  std::vector<std::string> categories;
  QGridLayout* map_grid = findChild<QGridLayout*>("mapGrid");
  deleteWidgets(map_grid);
  Coordinate dimensions = parser.getDimensions();
  createButtonsMapGrid(map_grid, dimensions.x, dimensions.y, -1, -1);
  QPixmap wood_pix(WOOD_WALL_PATH);
  QPixmap rock_pix(ROCK_WALL_PATH);
  QPixmap blue_pix(BLUE_WALL_PATH);
  QPixmap stone_pix(STONE_WALL_PATH);
  QPixmap rpg_pix(RPG_PATH);
  QPixmap chain_pix(CHAIN_GUN_PATH);
  QPixmap machine_pix(MACHINE_GUN_PATH);
  QPixmap locked_pix(LOCKED_DOOR_PATH);
  QPixmap unlocked_pix(UNLOCKED_DOOR_PATH);
  QPixmap fake_pix(FAKE_WALL_PATH);
  QPixmap barrel_pix(BARREL_PATH);
  QPixmap table_pix(TABLE_PATH);
  QPixmap bullets_pix(BULLETS_PATH);
  QPixmap chest_pix(CHEST_PATH);
  QPixmap cross_pix(CROSS_PATH);
  QPixmap crown_pix(CROWN_PATH);
  QPixmap goblet_pix(GOBLET_PATH);
  QPixmap food_pix(FOOD_PATH);
  QPixmap key_pix(KEY_PATH);
  QPixmap medic_pix(MEDKIT_PATH);
  QPixmap water_pix(WATER_PATH);
  QPixmap player_pix(PLAYER_PATH);

  categories.push_back("scenarios");
  categories.push_back("items");
  categories.push_back("players");

  for (auto& category: categories) {
    for (auto& items: parser.getSpecificCategory(category)) {
      for (auto& positions: items.second) {
        QGridButton* button = qobject_cast<QGridButton*>(map_grid->itemAtPosition(positions.y, positions.x)->widget());
        if (items.first == WOOD_WALL_STRING) updateGridButton(button, QIcon(wood_pix), WOOD_WALL_STRING);
        else if (items.first == ROCK_WALL_STRING) updateGridButton(button, QIcon(rock_pix), ROCK_WALL_STRING);
        else if (items.first == BLUE_WALL_STRING) updateGridButton(button, QIcon(blue_pix), BLUE_WALL_STRING);
        else if (items.first == STONE_WALL_STRING) updateGridButton(button, QIcon(stone_pix), STONE_WALL_STRING);
        else if (items.first == UNLOCKED_STRING) updateGridButton(button, QIcon(unlocked_pix), UNLOCKED_STRING);
        else if (items.first == FAKE_WALL_STRING) updateGridButton(button, QIcon(fake_pix), FAKE_WALL_STRING);
        else if (items.first == RPG_STRING) updateGridButton(button, QIcon(rpg_pix), RPG_STRING);
        else if (items.first == CHAIN_STRING) updateGridButton(button, QIcon(chain_pix), CHAIN_STRING);
        else if (items.first == MACHINE_STRING) updateGridButton(button, QIcon(machine_pix), MACHINE_STRING);
        else if (items.first == LOCKED_STRING) updateGridButton(button, QIcon(locked_pix), LOCKED_STRING);
        else if (items.first == BARREL_STRING) updateGridButton(button, QIcon(barrel_pix), BARREL_STRING);
        else if (items.first == TABLE_STRING) updateGridButton(button, QIcon(table_pix), TABLE_STRING);
        else if (items.first == BULLETS_STRING) updateGridButton(button, QIcon(bullets_pix), BULLETS_STRING);
        else if (items.first == CHEST_STRING) updateGridButton(button, QIcon(chest_pix), CHEST_STRING);
        else if (items.first == GOBLET_STRING) updateGridButton(button, QIcon(goblet_pix), GOBLET_STRING);
        else if (items.first == CROSS_STRING) updateGridButton(button, QIcon(cross_pix), CROSS_STRING);
        else if (items.first == CROWN_STRING) updateGridButton(button, QIcon(crown_pix), CROWN_STRING);
        else if (items.first == FOOD_STRING) updateGridButton(button, QIcon(food_pix), FOOD_STRING);
        else if (items.first == KEY_STRING) updateGridButton(button, QIcon(key_pix), KEY_STRING);
        else if (items.first == MEDKIT_STRING) updateGridButton(button, QIcon(medic_pix), MEDKIT_STRING);
        else if (items.first == WATER_STRING) updateGridButton(button, QIcon(water_pix), WATER_STRING);
        else if (items.first.length() == 1) updateGridButton(button, QIcon(player_pix), PLAYER_STRING);
      }
    }
  }
}

void Editor::createMapGrid() {
  QGridLayout* map_grid = findChild<QGridLayout*>("mapGrid");
  QWidget* scroll_area_content = new QWidget;
  scroll_area_content->setStyleSheet("QWidget{background-color: #29172B;}");
  scroll_area_content->setLayout(map_grid);
  QScrollArea* scroll_area = findChild<QScrollArea*>("scrollArea");
  scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  scroll_area->setWidgetResizable(true);
  scroll_area->setWidget(scroll_area_content);
  createButtonsMapGrid(map_grid, DEF_WIDTH, DEF_HEIGHT, -1, -1);
}

void Editor::updateGridButtonWithCursor(QGridButton* button) {
  QIcon icon(cursor().pixmap());
  updateGridButton(button, icon, currentCursor.c_str());
}

QMenu* Editor::createGridButtonMenu(QGridButton* button) {
  QPixmap wood_pix(WOOD_WALL_PATH);
  QPixmap rock_pix(ROCK_WALL_PATH);
  QPixmap blue_pix(BLUE_WALL_PATH);
  QPixmap stone_pix(STONE_WALL_PATH);
  QPixmap rpg_pix(RPG_PATH);
  QPixmap chain_pix(CHAIN_GUN_PATH);
  QPixmap machine_pix(MACHINE_GUN_PATH);
  QPixmap locked_pix(LOCKED_DOOR_PATH);
  QPixmap unlocked_pix(UNLOCKED_DOOR_PATH);
  QPixmap fake_pix(FAKE_WALL_PATH);
  QPixmap barrel_pix(BARREL_PATH);
  QPixmap table_pix(TABLE_PATH);
  QPixmap bullets_pix(BULLETS_PATH);
  QPixmap chest_pix(CHEST_PATH);
  QPixmap cross_pix(CROSS_PATH);
  QPixmap crown_pix(CROWN_PATH);
  QPixmap goblet_pix(GOBLET_PATH);
  QPixmap food_pix(FOOD_PATH);
  QPixmap key_pix(KEY_PATH);
  QPixmap medic_pix(MEDKIT_PATH);
  QPixmap water_pix(WATER_PATH);
  QPixmap player_pix(PLAYER_PATH);

  QIcon wood_icon(wood_pix);
  QIcon rock_icon(rock_pix);
  QIcon blue_icon(blue_pix);
  QIcon stone_icon(stone_pix);
  QIcon rpg_icon(rpg_pix);
  QIcon chain_icon(chain_pix);
  QIcon machine_icon(machine_pix);
  QIcon locked_icon(locked_pix);
  QIcon unlocked_icon(unlocked_pix);
  QIcon fake_icon(fake_pix);
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
  QIcon player_icon(player_pix);

  QMenu* menu = new QMenu();
  QMenu* menu_walls = new QMenu("Scenario");
  QMenu* menu_weapons = new QMenu("Weapons");
  QMenu* menu_items = new QMenu("Items");
  QMenu* menu_players= new QMenu("Players");

  menu_walls->setIcon(wood_icon);
  menu_weapons->setIcon(rpg_icon);
  menu_items->setIcon(medic_icon);
  menu_players->setIcon(player_icon);

  QAction* wood_action = menu_walls->addAction(wood_icon, "Wood wall");
  QAction* rock_action = menu_walls->addAction(rock_icon, "Rock wall");
  QAction* blue_action = menu_walls->addAction(blue_icon, "Blue wall");
  QAction* stone_action = menu_walls->addAction(stone_icon, "Stone wall");
  QAction* locked_action = menu_walls->addAction(locked_icon, "Locked door");
  QAction* unlocked_action = menu_walls->addAction(unlocked_icon, "Unlocked door");
  QAction* fake_action = menu_walls->addAction(fake_icon, "Fake wall");
  QAction* barrel_action = menu_walls->addAction(barrel_icon, "Barrel");
  QAction* water_action = menu_walls->addAction(water_icon, "Water puddle");
  QAction* table_action = menu_walls->addAction(table_icon, "Table");
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
  QAction* player_action = menu_players->addAction(player_icon, "Spawn");

  menu->addMenu(menu_walls);
  menu->addMenu(menu_items);
  menu->addMenu(menu_weapons);
  menu->addMenu(menu_players);

  connect(wood_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, wood_icon, WOOD_WALL_STRING));
  connect(rock_action,
          &QAction::triggered,
          std::bind(&Editor::updateGridButton, this, button, rock_icon, STONE_WALL_STRING));
  connect(blue_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, blue_icon, BLUE_WALL_STRING));
  connect(stone_action,
          &QAction::triggered,
          std::bind(&Editor::updateGridButton, this, button, stone_icon, STONE_WALL_STRING));
  connect(rpg_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, rpg_icon, RPG_STRING));
    connect(fake_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, fake_icon, FAKE_WALL_STRING));
    connect(unlocked_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, unlocked_icon, UNLOCKED_STRING));
  connect(chain_action,
          &QAction::triggered,
          std::bind(&Editor::updateGridButton, this, button, chain_icon, CHAIN_STRING));
  connect(machine_action,
          &QAction::triggered,
          std::bind(&Editor::updateGridButton, this, button, machine_icon, MACHINE_STRING));
  connect(locked_action,
          &QAction::triggered,
          std::bind(&Editor::updateGridButton, this, button, locked_icon, LOCKED_STRING));
  connect(barrel_action,
          &QAction::triggered,
          std::bind(&Editor::updateGridButton, this, button, barrel_icon, BARREL_STRING));
  connect(table_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, table_icon, TABLE_STRING));
  connect(bullets_action,
          &QAction::triggered,
          std::bind(&Editor::updateGridButton, this, button, bullets_icon, BULLETS_STRING));
  connect(chest_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, chest_icon, CHEST_STRING));
  connect(cross_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, cross_icon, CROSS_STRING));
  connect(crown_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, crown_icon, CROWN_STRING));
  connect(goblet_action,
          &QAction::triggered,
          std::bind(&Editor::updateGridButton, this, button, goblet_icon, GOBLET_STRING));
  connect(food_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, food_icon, FOOD_STRING));
  connect(key_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, key_icon, KEY_STRING));
  connect(medic_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, medic_icon, MEDKIT_STRING));
  connect(water_action,
          &QAction::triggered,
          std::bind(&Editor::updateGridButton, this, button, water_icon, WATER_STRING));
    connect(player_action, &QAction::triggered, std::bind(&Editor::updateGridButton, this, button, player_icon, PLAYER_STRING));

  return menu;
}

void Editor::updateGridButton(QGridButton* button, QIcon icon, const char* texture) {
  button->setIcon(icon);
  button->setProperty("texture", QVariant(texture));
}

void Editor::exportMap() {
  /* Height and width input */
  QLineEdit* input_height = findChild<QLineEdit*>("inputHeight");
  QLineEdit* input_width = findChild<QLineEdit*>("inputWidth");
  QString q_height = QString("%1").arg(input_height->text());
  QString q_width = QString("%1").arg(input_width->text());
  std::string height = q_height.toStdString();
  std::string width = q_width.toStdString();
  if (height.empty()) height = "14";
  if (width.empty()) width = "14";

  std::unordered_map<std::string, std::vector<std::pair <int, int>>> positions;

  std::vector<std::pair<int, int>> wood_positions;
  std::vector<std::pair<int, int>> rock_positions;
  std::vector<std::pair<int, int>> stone_positions;
  std::vector<std::pair<int, int>> blue_positions;
  std::vector<std::pair<int, int>> locked_positions;
  std::vector<std::pair<int, int>> unlocked_positions;
  std::vector<std::pair<int, int>> fake_positions;
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
  std::vector<std::pair<int, int>> barrel_positions;
  std::vector<std::pair<int, int>> table_positions;
  std::vector<std::pair<int, int>> water_positions;
  std::vector<std::pair<int, int>> player_positions;

  positions[WOOD_WALL_STRING] = wood_positions;
  positions[STONE_WALL_STRING] = rock_positions;
  positions[BLUE_WALL_STRING] = stone_positions;
  positions[ROCK_WALL_STRING] = blue_positions;
  positions[RPG_STRING] = locked_positions;
  positions[CHAIN_STRING] = unlocked_positions;
  positions[MACHINE_STRING] = fake_positions;
  positions[BULLETS_STRING] = rpg_positions;
  positions[CHEST_STRING] = chain_positions;
  positions[GOBLET_STRING] = machine_positions;
  positions[CROSS_STRING] = bullets_positions;
  positions[CROWN_STRING] = chest_positions;
  positions[FOOD_STRING] = goblet_positions;
  positions[KEY_STRING] = cross_positions;
  positions[MEDKIT_STRING] = crown_positions;
  positions[LOCKED_STRING] = food_positions;
  positions[UNLOCKED_STRING] = key_positions;
  positions[FAKE_WALL_STRING] = medkit_positions;
  positions[BARREL_STRING] = barrel_positions;
  positions[TABLE_STRING] = table_positions;
  positions[WATER_STRING] = water_positions;
  positions [PLAYER_STRING] = player_positions;

  QGridLayout* map_grid = findChild<QGridLayout*>("mapGrid");
  for (int i = 0; i < map_grid->rowCount(); ++i) {
    for (int j = 0; j < map_grid->columnCount(); ++j) {
      QGridButton* button_grid = qobject_cast<QGridButton*>(map_grid->itemAtPosition(i, j)->widget());
      std::string variantTexture = button_grid->property("texture").toString().toStdString();
      if (positions.find(variantTexture) != positions.end()){
          positions[button_grid->property("texture").toString().toStdString().c_str()].emplace_back(i, j);
      }
    }
  }



  MapExporter exporter(width, height, positions);

  std::string savePath = saveYamlPath();
  if (savePath.empty()) return;
  std::fstream file(savePath, std::ios::out);
  file << exporter.getMapParsed();
  file.close();
}

void Editor::refreshMapGrid() {
  /* Height and width input */
  QLineEdit* input_height = findChild<QLineEdit*>("inputHeight");
  QLineEdit* input_width = findChild<QLineEdit*>("inputWidth");
  QString height = QString("%1").arg(input_height->text());
  QString width = QString("%1").arg(input_width->text());

  QGridLayout* map_grid = findChild<QGridLayout*>("mapGrid");
  int grid_rows = map_grid->rowCount();
  int grid_cols = map_grid->columnCount();
  int new_cols = width.toInt();
  int new_rows = height.toInt();
  int rows = grid_rows >= new_rows ? grid_rows : new_rows;
  int cols = grid_cols >= new_cols ? grid_cols : new_cols;

  createButtonsMapGrid(map_grid, rows, cols, grid_rows, grid_cols);

  // TODO Agregar sacar celdas
}

void Editor::createButtonsMapGrid(QGridLayout* map_grid, int rows, int cols, int grid_rows, int grid_cols) {
  QPixmap pixmap(EMPTY_PATH);
  QIcon buttonIcon(pixmap);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (i < grid_rows && j < grid_cols) continue;
      QGridButton* button_grid = new QGridButton();
      button_grid->setStyleSheet("QGridButton::menu-indicator{width:0px;}");
      button_grid->setMaximumSize(BUTTON_MAXIMUM_SIZE, BUTTON_MAXIMUM_SIZE);
      button_grid->setMinimumSize(BUTTON_MINIMUM_SIZE, BUTTON_MINIMUM_SIZE);
      button_grid->setIcon(buttonIcon);
      button_grid->setIconSize(pixmap.rect().size());
      QMenu* menu = createGridButtonMenu(button_grid);
      button_grid->setMenu(menu);
      connect(button_grid,
              &QGridButton::rightClicked,
              this,
              std::bind(&Editor::updateGridButtonWithCursor, this, button_grid));
      map_grid->addWidget(button_grid, i, j);
    }
  }
}

std::string Editor::saveYamlPath() {
  return QFileDialog::getSaveFileName(this,
                                      tr("Save map"), "../maps/untitled.yaml",
                                      tr("YAML file (*.yaml)")).toStdString();
}

std::string Editor::getYamlPath() {
  return QFileDialog::getOpenFileName(this,
                                      tr("Load map"), "../maps/",
                                      tr("YAML file (*.yaml)")).toStdString();
}

void Editor::connectEvents() {
  QPushButton* button_export = findChild<QPushButton*>("buttonExport");
  QPushButton* button_refresh = findChild<QPushButton*>("buttonRefresh");
  QPushButton* button_scenario = findChild<QPushButton*>("buttonScenario");
  QPushButton* button_items = findChild<QPushButton*>("buttonItems");
  QPushButton* button_weapons = findChild<QPushButton*>("buttonWeapons");
  QPushButton* button_players = findChild<QPushButton*>("buttonPlayers");

  connect(button_export, &QPushButton::clicked, this, &Editor::exportMap);
  connect(button_refresh, &QPushButton::clicked, this, &Editor::refreshMapGrid);
  connect(button_scenario, &QPushButton::clicked, this, std::bind(&Editor::updateTextureGrid, this, "walls"));
  connect(button_items, &QPushButton::clicked, this, std::bind(&Editor::updateTextureGrid, this, "items"));
  connect(button_weapons, &QPushButton::clicked, this, std::bind(&Editor::updateTextureGrid, this, "weapons"));
  connect(button_players, &QPushButton::clicked, this, std::bind(&Editor::updateTextureGrid, this, "players"));
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

void Editor::renderScenarioGrid(QGridLayout* texture_grid) {
  std::vector<std::pair<QIcon, std::string>> icons;

  QPixmap wood_pix(WOOD_WALL_PATH);
  QPixmap rock_pix(ROCK_WALL_PATH);
  QPixmap blue_pix(BLUE_WALL_PATH);
  QPixmap stone_pix(STONE_WALL_PATH);
  QPixmap unlocked_pix(UNLOCKED_DOOR_PATH);
  QPixmap locked_pix(LOCKED_DOOR_PATH);
  QPixmap fake_pix(FAKE_WALL_PATH);
  QPixmap barrel_pix(BARREL_PATH);
  QPixmap table_pix(TABLE_PATH);
  QPixmap water_pix(WATER_PATH);

  icons.emplace_back(QIcon(wood_pix), WOOD_WALL_STRING);
  icons.emplace_back(QIcon(rock_pix), ROCK_WALL_STRING);
  icons.emplace_back(QIcon(blue_pix), BLUE_WALL_STRING);
  icons.emplace_back(QIcon(stone_pix), STONE_WALL_STRING);
  icons.emplace_back(QIcon(locked_pix), LOCKED_STRING);
  icons.emplace_back(QIcon(unlocked_pix), UNLOCKED_STRING);
  icons.emplace_back(QIcon(fake_pix), FAKE_WALL_STRING);
  icons.emplace_back(QIcon(barrel_pix), BARREL_STRING);
  icons.emplace_back(QIcon(table_pix), TABLE_STRING);
  icons.emplace_back(QIcon(water_pix), WATER_STRING);

  renderTextureGrid(texture_grid, icons);
}

void Editor::changeCursor(QPixmap pix, std::string texture_name) {
  setCursor(QCursor(pix));
  currentCursor = texture_name;
}

void Editor::renderItemsGrid(QGridLayout* texture_grid) {
  std::vector<std::pair<QIcon, std::string>> icons;

  QPixmap bullets_pix(BULLETS_PATH);
  QPixmap chest_pix(CHEST_PATH);
  QPixmap cross_pix(CROSS_PATH);
  QPixmap crown_pix(CROWN_PATH);
  QPixmap goblet_pix(GOBLET_PATH);
  QPixmap food_pix(FOOD_PATH);
  QPixmap key_pix(KEY_PATH);
  QPixmap medic_pix(MEDKIT_PATH);

  icons.emplace_back(QIcon(bullets_pix), BULLETS_STRING);
  icons.emplace_back(QIcon(chest_pix), CHEST_STRING);
  icons.emplace_back(QIcon(cross_pix), CROSS_STRING);
  icons.emplace_back(QIcon(crown_pix), CROWN_STRING);
  icons.emplace_back(QIcon(goblet_pix), GOBLET_STRING);
  icons.emplace_back(QIcon(food_pix), FOOD_STRING);
  icons.emplace_back(QIcon(key_pix), KEY_STRING);
  icons.emplace_back(QIcon(medic_pix), MEDKIT_STRING);

  renderTextureGrid(texture_grid, icons);
}

void Editor::renderWeaponsGrid(QGridLayout* texture_grid) {
  std::vector<std::pair<QIcon, std::string>> icons;

  QPixmap rpg_pix(RPG_PATH);
  QPixmap chain_pix(CHAIN_GUN_PATH);
  QPixmap machine_pix(MACHINE_GUN_PATH);

  icons.emplace_back(QIcon(rpg_pix), RPG_STRING);
  icons.emplace_back(QIcon(chain_pix), CHAIN_STRING);
  icons.emplace_back(QIcon(machine_pix), MACHINE_STRING);

  renderTextureGrid(texture_grid, icons);
}

void Editor::renderPlayersGrid(QGridLayout* texture_grid) {
  std::vector<std::pair<QIcon, std::string>> icons;

  QPixmap player_pix(PLAYER_PATH);

  icons.emplace_back(QIcon(player_pix), PLAYER_STRING);

  renderTextureGrid(texture_grid, icons);
}

void Editor::renderTextureGrid(QGridLayout* texture_grid, std::vector<std::pair<QIcon, std::string>> icons) {
  int i = 0;
  int j = 0;
  for (auto& icon: icons) {
    QPushButton* button = new QPushButton();
    button->setIcon(icon.first);
    button->setFlat(true);
    button->setIconSize(QSize(125, 125));
    connect(button,
            &QPushButton::clicked,
            this,
            std::bind(&Editor::changeCursor, this, icon.first.pixmap(CURSOR_SIZE), icon.second));
    texture_grid->addWidget(button, j, i);
    ++i;
    if (i % TEXTURES_GRID_WIDTH == 0) {
      ++j;
      i = 0;
    }
  }
}

void Editor::deleteWidgets(QGridLayout* layout) {
  QLayoutItem* item;
  while ((item = layout->takeAt(0)) != NULL) {
    delete item->widget();
    delete item;
  }
}

