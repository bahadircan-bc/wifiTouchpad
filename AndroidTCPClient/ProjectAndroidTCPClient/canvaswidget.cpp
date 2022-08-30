#include "canvaswidget.h"

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget{parent}
{

}

void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(5);
    painter.setPen(pen);
    painter.drawPoint(50,50);

    QStringList indCoords = coordinates.split(";");
    qDebug() << "individual coords: " << indCoords;
    Q_FOREACH(QString coord, indCoords)
    {
        if(coord.size() <= 1) return;

        QStringList xAndY = coord.split(",");
        qDebug() << "\nX and Y: " << xAndY;

        if(xAndY.size() <= 1) return;
        painter.drawPoint(QPoint(xAndY[0].toInt(), xAndY[1].toInt()));
    }
}

void CanvasWidget::drawPoints(QString coordinates)
{
    this->coordinates = coordinates;
    update();
}
