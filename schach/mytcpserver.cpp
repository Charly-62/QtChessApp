#include "mytcpserver.h"

MyTCPServer::MyTCPServer(Game* gameInstance, QObject *parent)
    : Netzwerk(gameInstance, parent), server(new QTcpServer(this)), clientSocket(nullptr)
{
    server = new QTcpServer(this);
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

    if(clientSocket) {
        clientSocket->disconnectFromHost();
        delete clientSocket;
        clientSocket = nullptr;
    }
}

void MyTCPServer::onClientConnecting() {
    clientSocket = server->nextPendingConnection();
    if(clientSocket) {
        QHostAddress address = clientSocket->peerAddress();
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
        connect(clientSocket, &QTcpSocket::disconnected, this, &MyTCPServer::onClientDisconnected);
    }
}

void MyTCPServer::onClientDisconnected() {
    QHostAddress address = clientSocket->peerAddress();
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
    clientSocket->deleteLater();
    clientSocket = nullptr;
}

bool MyTCPServer::isListening() {
    return server->isListening();
}
