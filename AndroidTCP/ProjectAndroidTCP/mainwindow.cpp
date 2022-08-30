#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    communicator = new Communicator(nullptr);
    commThread = new QThread();

    setBindings();

    communicator->moveToThread(commThread);
    commThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::listenButtonClicked()
{
    QString address = ui->lineEditAddress->text();
    QString port = ui->lineEditPort->text();

    emit startListeningSignal(address, port);
}

void MainWindow::receivedLog(QString log)
{
    ui->textEditHistory->append("log: " + log);
}

void MainWindow::showMsg(QByteArray msg)
{
    ui->textEditHistory->append("Client: " + msg);
}

void MainWindow::sendButtonClicked()
{
    emit sendMsgSignal(ui->lineEditMsgBox->text());
    ui->lineEditMsgBox->clear();
}

void MainWindow::setBindings()
{
    connect(ui->pushButtonListen, &QPushButton::released, this, &MainWindow::listenButtonClicked);
    connect(this, &MainWindow::startListeningSignal, communicator, &Communicator::startListening);
    connect(ui->pushButtonClose, &QPushButton::released, communicator, &Communicator::stopListening);
    connect(communicator, &Communicator::log, this, &MainWindow::receivedLog);
    connect(communicator, &Communicator::messageReceived, this, &MainWindow::showMsg);
    connect(ui->pushButtonSend, &QPushButton::released, this, &MainWindow::sendButtonClicked);
    connect(this, &MainWindow::sendMsgSignal, communicator, &Communicator::writeSocket);
    connect(ui->touchAreaWidget, &TouchPad::sendMousePos, communicator, &Communicator::writeSocket);
}

