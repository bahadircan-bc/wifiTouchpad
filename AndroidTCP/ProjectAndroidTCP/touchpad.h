#ifndef TOUCHPAD_H
#define TOUCHPAD_H

#include <QWidget>
#include <QDebug>
#include <QMouseEvent>

class TouchPad : public QWidget
{
    Q_OBJECT
public:
    explicit TouchPad(QWidget *parent = nullptr);

    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
signals:
    void sendMousePos(QString);

};

#endif // TOUCHPAD_H
