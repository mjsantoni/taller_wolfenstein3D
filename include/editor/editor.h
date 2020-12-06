#ifndef TP_WOLFENSTEIN_EDITOR_H
#define TP_WOLFENSTEIN_EDITOR_H

#include <QMainWindow>

class Editor : public QMainWindow {
public:
    explicit Editor(QMainWindow *parent = 0);
private:
    void exportMap();
    void connectEvents();
};

#endif //TP_WOLFENSTEIN_EDITOR_H
