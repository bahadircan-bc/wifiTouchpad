#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>

class Communicator : public QObject
{
    Q_OBJECT
public:
    explicit Communicator(QObject *parent = nullptr);

public slots:
    void incomingConnection();
    void connectionError(QTcpSocket::SocketError);
    void startListening(QString, QString);
    void stopListening();
    void disconnect();

    void writeSocket(QString);
    void readSocket();

signals:
    void messageReceived(QByteArray);
    void connectionStatus(bool);
    void log(QString);

private:
    QTcpServer* _server;
    QTcpSocket* _socket;
    bool connected = false;
};

#endif // COMMUNICATOR_H
