#ifndef TP_WOLFENSTEIN_EDITOR_H
#define TP_WOLFENSTEIN_EDITOR_H

#include <QWidget>

class Editor : public QWidget {
public:
    explicit Editor(QWidget *parent = 0);
private:
    void exportMap();
    void connectEvents();
};

#endif //TP_WOLFENSTEIN_EDITOR_H
