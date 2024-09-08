#include "mytcpclient.h"

MyTCPClient::MyTCPClient(Game* gameInstance, QObject *parent)
    : Netzwerk(gameInstance, parent) {
    initializeSocket();
    connect(_socket, &QTcpSocket::connected, this, &MyTCPClient::connected);
    connect(_socket, &QTcpSocket::disconnected, this, &MyTCPClient::disconnected);
    connect(_socket, &QTcpSocket::stateChanged, this, &MyTCPClient::socket_stateChanged);
}

void MyTCPClient::connectToHost(QString ip, int port) {
    initializeSocket(); // Ensure the socket is initialized
    if(_socket->isOpen()) {

        if(ip == _ip && port == _port) {
            return;
        }

        _socket->close();
    }

    _ip = ip;
    _port = port;
    _socket->connectToHost(_ip, _port);

}


void MyTCPClient::disconnect() {
    _socket->close();
}

bool MyTCPClient::isConnected() {
    return _socket->state() == QAbstractSocket::ConnectedState;
}

void MyTCPClient::socket_stateChanged(QAbstractSocket::SocketState state) {

    if(state == QAbstractSocket::UnconnectedState) {
        _socket->close();
    }

    emit stateChanged(state);

}

QAbstractSocket::SocketState MyTCPClient::state() {
    return _socket->state();
}
