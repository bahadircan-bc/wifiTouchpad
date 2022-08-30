#include "touchpad.h"

TouchPad::TouchPad(QWidget *parent)
    : QWidget{parent}
{

}

void TouchPad::mousePressEvent(QMouseEvent *event)
{
    QPoint p = event->pos();
    QString posMsg = QString::number(p.x()) + ", " + QString::number(p.y()) + ";";

    qDebug() << "emitting posMsg with: " << posMsg;
    emit sendMousePos(posMsg);
}

void TouchPad::mouseMoveEvent(QMouseEvent *event)
{
    QPoint p = event->pos();
    QString posMsg = QString::number(p.x()) + ", " + QString::number(p.y()) + ";";

    qDebug() << "emitting posMsg with: " << posMsg;
    emit sendMousePos(posMsg);
}
