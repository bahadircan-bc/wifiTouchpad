#include "client.h"

Client::Client(QObject *parent)
    : QObject{parent}
{
    _socket = new QTcpSocket(this);

    connect(_socket, &QTcpSocket::readyRead, this, &Client::socketRead);
}

void Client::connectToHost(QString address, QString port)
{
    if(address == "")
    {
        emit log("address is empty");
        return;
    }
    QHostAddress _address(address);
    if(_address.isNull())
    {
        emit log("address is null");
        return;
    }
    _socket->connectToHost(address, port.toUInt(), QTcpSocket::ReadWrite);
    if(!_socket->isOpen())
    {
        emit log("socket is not open");
        emit log(_socket->errorString());
    }
    else
    {
        emit log("socket is open on " + _socket->localAddress().toString());
    }
}

void Client::disconnectFromHost()
{
    if(!_socket->isOpen()) return;

    _socket->close();
    emit log("socket is closed");
}

void Client::handleError(QAbstractSocket::SocketError socketError)
{
    emit log("error occured.. " + _socket->errorString());
}

void Client::socketWrite(QString msg)
{
    if(!(_socket->isOpen()) || !(_socket->isWritable())) return;

    qDebug()<< "client: writing to socket";
    _socket->write(QByteArray(msg.toStdString().c_str()));
}

void Client::socketRead()
{
    QByteArray data = _socket->readAll();
    emit msgReceived(data);
}
