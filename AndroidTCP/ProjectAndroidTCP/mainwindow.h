#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QPushButton>
#include "communicator.h"
#include "touchpad.h"

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
    void listenButtonClicked();
    void receivedLog(QString);

    void showMsg(QByteArray);
    void sendButtonClicked();

    //void touchAreaClicked();

signals:
    void startListeningSignal(QString, QString);
    void stopListeningSignal();

    void sendMsgSignal(QString);

private:
    Ui::MainWindow *ui;
    Communicator* communicator;
    QThread* commThread;

    void setBindings();

};
#endif // MAINWINDOW_H
