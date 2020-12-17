#include "editor/QGridButton.h"
#include "editor/moc_QGridButton.cpp"

QGridButton::QGridButton(QWidget *parent) : QPushButton(parent){}

void QGridButton::mousePressEvent(QMouseEvent *e){
    if(e->button()==Qt::RightButton){
        emit rightClicked();
    }
    else if(e->button()==Qt::LeftButton) {
        emit clicked();
    }
}