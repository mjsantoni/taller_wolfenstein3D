#ifndef TP_WOLFENSTEIN_EDITOR_H
#define TP_WOLFENSTEIN_EDITOR_H

#include <QMainWindow>
#include "QGridButton.h"
#include <QActionGroup>
#include <QLabel>
#include <QGridLayout>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

class Editor : public QMainWindow {
public:
    explicit Editor(QMainWindow *parent = 0);
    void updateGridButton(QGridButton *button, QIcon icon, const char *texture);
private:
    void createMapGrid();
    void refreshMapGrid();
    QMenu* createGridButtonMenu(QGridButton* button);
    void exportMap();
    void connectEvents();
    std::string getYamlPath();
    std::string saveYamlPath();
    void loadMap(std::string path);
    void updateTextureGrid(std::string texture_type);

    void createTextureGrid();

    void renderScenarioGrid(QGridLayout *texture_grid);

    void renderItemsGrid(QGridLayout *texture_grid);

    void renderPlayersGrid(QGridLayout *texture_grid);

    void dragEnterEvent(QDragEnterEvent *e);

    void dropEvent(QDropEvent *e);

    void dragMoveEvent(QDragMoveEvent *event);

    void dragLeaveEvent(QDragLeaveEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void updateGridButtonWithCursor(QGridButton *button);

    void renderWeaponsGrid(QGridLayout *pLayout);

    void changeCursor(QPixmap pix, std::string texture_name);

    void renderTextureGrid(QGridLayout *texture_grid, std::vector<std::pair<QIcon, std::string>> icons);

    std::string currentCursor;

    void createButtonsMapGrid(QGridLayout *mapGrid, int rows, int cols, int gridRows, int gridCols);

    void deleteWidgets(QGridLayout *pLayout);
};

#endif //TP_WOLFENSTEIN_EDITOR_H
