#include "mytcpclient.h"
#include <QTimer>

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

void MyTCPClient::tryReconnect() {
    emit logMessage("Attempting to reconnect...");
    attemptReconnect(5);  // Start the attempt process with max 5 attempts
}

void MyTCPClient::attemptReconnect(int remainingAttempts) {
    if (remainingAttempts <= 0) {
        emit logMessage("Failed to reconnect after 5 attempts.");
        return;
    }

    // Try reconnecting
    QTimer::singleShot(3000, this, [this, remainingAttempts]() {
        _socket->connectToHost(_ip, _port);

        // Wait for the connection to establish asynchronously
        if (_socket->waitForConnected(5000)) { // Wait for up to 5 seconds
            emit logMessage("Reconnected successfully!");
        } else {
            if(remainingAttempts - 1 > 0) {
            emit logMessage(QString("Reconnection attempt failed. %1 attempts remaining.").arg(remainingAttempts - 1));
            }
            attemptReconnect(remainingAttempts - 1);  // Try again recursively
        }
    });
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
