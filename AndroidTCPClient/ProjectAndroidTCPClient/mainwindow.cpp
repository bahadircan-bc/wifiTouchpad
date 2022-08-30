#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new Client(nullptr);
    clientThread = new QThread();

    client->moveToThread(clientThread);
    clientThread->start();



    setBindings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectButtonClicked()
{
    QString address = ui->lineEditAddress->text();
    QString port = ui->lineEditPort->text();

    emit connectToHostSignal(address, port);
}

void MainWindow::receivedLog(QString log)
{
    ui->textEditHistory->append("log: " + log);
}

void MainWindow::showMsg(QByteArray msg)
{
    ui->textEditHistory->append("Server: " + msg);
    emit drawOnCanvas(QString(msg));
    moveMouseCursor(QString(msg));
}

void MainWindow::sendButtonClicked()
{
    qDebug() << "sending message ";
    emit sendMsg(ui->lineEditMsgBox->text());
    ui->lineEditMsgBox->clear();
}

void MainWindow::moveMouseCursor(QString coordinates)
{
    QCursor cur;

    QStringList indCoords = coordinates.split(";");
    qDebug() << "individual coords: " << indCoords;
    Q_FOREACH(QString coord, indCoords)
    {
        if(coord.size() <= 1) return;

        QStringList xAndY = coord.split(",");
        qDebug() << "\nX and Y: " << xAndY;

        if(xAndY.size() <= 1) return;
        cur.setPos(xAndY[0].toInt(), xAndY[1].toInt());
    }
}


void MainWindow::setBindings()
{
    connect(ui->pushButtonConnect, &QPushButton::released, this, &MainWindow::connectButtonClicked);
    connect(this, &MainWindow::connectToHostSignal, client, &Client::connectToHost);
    connect(client, &Client::log, this, &MainWindow::receivedLog);
    connect(ui->pushButtonDisconnect, &QPushButton::released, client, &Client::disconnectFromHost);
    connect(client, &Client::msgReceived, this, &MainWindow::showMsg);
    connect(ui->pushButtonSend, &QPushButton::released, this, &MainWindow::sendButtonClicked);
    connect(this, &MainWindow::sendMsg, client, &Client::socketWrite);
    connect(this, &MainWindow::drawOnCanvas, ui->canvasWidget, &CanvasWidget::drawPoints);
}
