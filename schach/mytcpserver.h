#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "netzwerk.h"

class MyTCPServer : public Netzwerk
{
    Q_OBJECT

public:
    explicit MyTCPServer(Game* gameInstance, QObject *parent = nullptr);
    ~MyTCPServer();

    void startListening(int port);
    void stopListening();
    bool isListening();

signals:
    void clientStateChanged(QString clientInfo); // Signal for client connection/disconnection UI updates
    void serverStatus(QString status); // Signal for server status UI updates

private slots:
    void onClientConnecting();
    void onClientDisconnected();

private:
    QTcpServer* server;
};

#endif // MYTCPSERVER_H
