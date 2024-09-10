#include "mytcpserver.h"

MyTCPServer::MyTCPServer(Game* gameInstance, QObject *parent)
    : Netzwerk(gameInstance, parent), server(new QTcpServer(this))
{
    server = new QTcpServer(this);
    initializeSocket();
    connect(server, &QTcpServer::newConnection, this, &MyTCPServer::onClientConnecting);
}

MyTCPServer::~MyTCPServer() {
    stopListening();
    delete server;
}

void MyTCPServer::startListening(int port) {
    if(!server->listen(QHostAddress::Any, port)) {
        QString errorMsg = QString("Server could not start listening: %1").arg(server->errorString());
        emit serverStatus(errorMsg);
    } else {
        QString successMsg = QString("Server started listening on port: %1").arg(port);
        emit serverStatus(successMsg);
    }
}

void MyTCPServer::stopListening() {
    if(server->isListening()) {
        server->close();
    }

    if(_socket) {
        _socket->disconnectFromHost();
        delete _socket;
        _socket = nullptr;
    }
}

void MyTCPServer::onClientConnecting() {
    _socket = server->nextPendingConnection();
    if(_socket) {
        QHostAddress address = _socket->peerAddress();
        QString clientInfo;

        // Save IP as QString according to address type
        if (address.protocol() == QAbstractSocket::IPv4Protocol) {
            clientInfo = QString("New client connected: %1").arg(address.toString());
        } else if (address.protocol() == QAbstractSocket::IPv6Protocol) {
            // Check if it's an IPv6-mapped IPv4 address and extract the IPv4 part
            QString ipv6String = address.toString();
            if (ipv6String.startsWith("::ffff:")) {
                clientInfo = QString("New client connected: %1").arg(ipv6String.section("::ffff:", 1, 1));
            } else {
                clientInfo = QString("New client connected: %1").arg(ipv6String);
            }
        }

        emit clientStateChanged(clientInfo); // Emit signal to update UI
        // Handle client disconnection
        connect(_socket, &QTcpSocket::disconnected, this, &MyTCPServer::onClientDisconnected);
    }
}

void MyTCPServer::onClientDisconnected() {
    QHostAddress address = _socket->peerAddress();
    QString clientInfo;

    // Save IP as QString according to address type
    if (address.protocol() == QAbstractSocket::IPv4Protocol) {
        clientInfo = QString("Client disconnected: %1").arg(address.toString());
    } else if (address.protocol() == QAbstractSocket::IPv6Protocol) {
        // Check if it's an IPv6-mapped IPv4 address and extract the IPv4 part
        QString ipv6String = address.toString();
        if (ipv6String.startsWith("::ffff:")) {
            clientInfo = QString("Client disconnected: %1").arg(ipv6String.section("::ffff:", 1, 1));
        } else {
            clientInfo = QString("Client disconnected: %1").arg(ipv6String);
        }
    }
    emit clientStateChanged(clientInfo);
    _socket->deleteLater();
    _socket = nullptr;
}

bool MyTCPServer::isListening() {
    return server->isListening();
}
