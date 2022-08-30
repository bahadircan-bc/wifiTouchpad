#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

public slots:
    void connectToHost(QString, QString);
    void disconnectFromHost();
    void handleError(QAbstractSocket::SocketError);
    void socketWrite(QString);
    void socketRead();



signals:
    void log(QString);
    void msgReceived(QByteArray);

private:
    QTcpSocket* _socket;

};

#endif // CLIENT_H
