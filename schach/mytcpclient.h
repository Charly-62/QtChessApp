#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include "netzwerk.h"

class MyTCPClient : public Netzwerk
{
    Q_OBJECT
public:
    MyTCPClient(Game* gameInstance, QObject *parent = nullptr);

    /**
     * @brief Connects to a host
     */
    void connectToHost(QString ip, int port);
    void disconnect();
    QAbstractSocket::SocketState state();
    bool isConnected();

signals:
    void connected();
    void disconnected();
    void stateChanged(QAbstractSocket::SocketState);

private slots:
    void socket_stateChanged(QAbstractSocket::SocketState);

private:
    QTcpSocket _socket;
    QString _ip;
    int _port;

};

#endif // MYTCPCLIENT_H
