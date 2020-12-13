#ifndef TP_WOLFENSTEIN_EDITOR_H
#define TP_WOLFENSTEIN_EDITOR_H

#include <QMainWindow>
#include <QPushButton>
#include <QActionGroup>
#include <QLabel>

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

};

#endif //TP_WOLFENSTEIN_EDITOR_H
