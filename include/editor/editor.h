#ifndef TP_WOLFENSTEIN_EDITOR_H
#define TP_WOLFENSTEIN_EDITOR_H

#include <QMainWindow>
#include <QPushButton>
#include <QActionGroup>
#include <QLabel>
#include <QGridLayout>

class Editor : public QMainWindow {
public:
    explicit Editor(QMainWindow *parent = 0);
    void updateGridButton(QPushButton *button, QIcon &icon, const char *texture);
private:
    void createMapGrid();
    void refreshMapGrid();
    QMenu* createGridButtonMenu(QPushButton* button);
    void exportMap();
    void connectEvents();
    std::string getYamlPath();
    std::string saveYamlPath();
    void loadMap();
    void updateTextureGrid(std::string texture_type);

    void createTextureGrid();

    void renderWallsGrid(QGridLayout *texture_grid);

    void renderItemsGrid(QGridLayout *texture_grid);

    void renderPlayersGrid(QGridLayout *texture_grid);

    void changeCursor(QPixmap pix);
};

#endif //TP_WOLFENSTEIN_EDITOR_H
