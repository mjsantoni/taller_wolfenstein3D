#ifndef TP_WOLFENSTEIN_EDITOR_H
#define TP_WOLFENSTEIN_EDITOR_H

#include <QMainWindow>
#include <QPushButton>

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
};

#endif //TP_WOLFENSTEIN_EDITOR_H
