#include "communicator.h"

Communicator::Communicator(QObject *parent)
    : QObject{parent}
{
    _server = new QTcpServer(this);
    _socket = new QTcpSocket(this);

    connect(_server, &QTcpServer::newConnection, this, &Communicator::incomingConnection);
    connect(_server, &QTcpServer::acceptError, this, &Communicator::connectionError);
    connect(_socket, &QTcpSocket::readyRead, this, &Communicator::readSocket);
}

void Communicator::incomingConnection()
{
    _socket = _server->nextPendingConnection();
    if(!_socket->isValid()) return;

    _socket->open(QTcpSocket::ReadWrite);
    if(!(_socket->isOpen()))
    {
        connected = false;
        emit log("connection arrived but socket couldn't be opened");
        return;
    }
    connected = true;
    emit connectionStatus(connected);
    emit log("new connection");

    _socket->write("Hello Client!");
}

void Communicator::connectionError(QAbstractSocket::SocketError socketError)
{
    emit log(_server->errorString());
}

void Communicator::startListening(QString address, QString port)
{
    if(_server->isListening())
    {
        emit log("server is already listening");
        return;
    }
    QHostAddress _address = QHostAddress(address);
    quint16 _port = port.toUInt();

    if(_address.isNull())
    {
        emit log("address is not valid listening to any");
        _server->listen(QHostAddress::Any, _port);
    }

    _server->listen(_address, _port);
    emit log("listening on " + _server->serverAddress().toString() + " PORT: " + QString::number(_server->serverPort()));
}

void Communicator::stopListening()
{
    if(_server->isListening())
        _server->close();
}

void Communicator::disconnect()
{
    if(!connected) return;

    _socket->close();
    connected = false;
}

void Communicator::writeSocket(QString msg)
{
    _socket->write(QByteArray(msg.toStdString().c_str()));
}

void Communicator::readSocket()
{
    qDebug() << "reading the socket";
    QByteArray msg = _socket->readAll();
    emit messageReceived(msg);
}
