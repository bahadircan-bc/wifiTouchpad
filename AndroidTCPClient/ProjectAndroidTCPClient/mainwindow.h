#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QDebug>
#include <QPainter>
#include <QCursor>
#include "client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void connectButtonClicked();
    void receivedLog(QString);

    void showMsg(QByteArray);
    void sendButtonClicked();

    void moveMouseCursor(QString);

signals:
    void connectToHostSignal(QString, QString);
    void sendMsg(QString);

    void drawOnCanvas(QString);

private:
    Ui::MainWindow *ui;
    Client* client;
    QThread* clientThread;
    QPainter* painter;

    void setBindings();
};
#endif // MAINWINDOW_H
