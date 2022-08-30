#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QDebug>

class CanvasWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CanvasWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent*) override;

    QString coordinates;

public slots:
    void drawPoints(QString);

signals:

};

#endif // CANVASWIDGET_H
