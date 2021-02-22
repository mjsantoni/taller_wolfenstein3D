#ifndef TP_WOLFENSTEIN_QGRIDBUTTON_H
#define TP_WOLFENSTEIN_QGRIDBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class QGridButton : public QPushButton {
 Q_OBJECT
 public:
  explicit QGridButton(QWidget* parent = 0);

 private slots:
  void mousePressEvent(QMouseEvent* e);

 signals:
  void rightClicked();

 public slots:

};

#endif //TP_WOLFENSTEIN_QGRIDBUTTON_H
