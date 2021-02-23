#ifndef TP_WOLFENSTEIN_EDITOR_H
#define TP_WOLFENSTEIN_EDITOR_H

#include <QMainWindow>
#include <QActionGroup>
#include <QLabel>
#include <QGridLayout>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <QDebug>
#include <QFileDialog>
#include <algorithm>
#include <dirent.h>
#include "QGridButton.h"
#include "yaml-cpp/yaml.h"
#include "common/map_parser.h"
#include "common/coordinate.h"
#include "editor/map_exporter.h"
#include "ui_editor.h"
#include "editor/QGridButton.h"

/* This class is the main window of the editor app, handles events
 * updating buttons and saves and loads the maps created*/

class Editor : public QMainWindow {

 public:

  explicit Editor(std::string& path, QMainWindow* parent = 0);

  ~Editor();

  /*Loads the map from the file obtained in getYamlPath*/
  void loadMap(std::string path);

 private:
  /* Attribute to know whats the current texture name in te cursor */
  std::string current_cursor;

  void createMapGrid();

  /* Creates all the buttons needed on the map grid*/
  void createButtonsMapGrid(QGridLayout* map_grid, int rows, int cols, int grid_rows, int grid_cols);

  QMenu* createGridButtonMenu(QGridButton* button);

  void createTextureGrid();

  void updateGridButton(QGridButton* button, QIcon icon, const char* texture);

  /*Changes the grid of textures on the right side of the editor to the desired texture type (Scenario, items, etc)*/
  void updateTextureGrid(std::string texture_type);

  void updateGridButtonWithCursor(QGridButton* button);

  void refreshMapGrid();

  /*Exports the map while parsing it to the file selected in saveYamlPath()*/
  void exportMap();

  /*Connect the majority of the buttons to their action*/
  void connectEvents();

  std::string getYamlPath();

  std::string saveYamlPath();

  void renderItemsGrid(QGridLayout* texture_grid);

  void renderPlayersGrid(QGridLayout* texture_grid);

  void renderScenarioGrid(QGridLayout* texture_grid);

  void renderWeaponsGrid(QGridLayout* texture_grid);

  /* This method renders all the "render" wrappers with the vector of icons of the callee function.*/
  void renderTextureGrid(QGridLayout* texture_grid, std::vector<std::pair<QIcon, std::string>> icons);

  void changeCursor(QPixmap pix, std::string texture_name);

  /*Drag events used to implement the map drag and drop-load functionality*/
  void dropEvent(QDropEvent* e);

  void dragMoveEvent(QDragMoveEvent* event);

  void dragEnterEvent(QDragEnterEvent* e);

  void dragLeaveEvent(QDragLeaveEvent* event);

  /*Resets the texture on the cursor when pressed on any place of the window*/
  void mousePressEvent(QMouseEvent* event);

  /*Deletes all the widgets within a layout*/
  void deleteWidgets(QGridLayout* layout);

  void showLastModifiedFiles();
};

#endif //TP_WOLFENSTEIN_EDITOR_H
