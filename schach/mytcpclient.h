/**
 * @file mytcpclient.h
 * @brief This file contains the declaration of the client class.
 */

#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include "netzwerk.h"

#include <QTimer>

/**
 * @class MyTCPClient
 * @brief Handles the client-side TCP communication for the chess game.
 *
 * This class manages connecting to a remote server, handling reconnections,
 * and managing the state of the TCP socket for communication.
 */
class MyTCPClient : public Netzwerk
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for the MyTCPClient class.
     * @param gameInstance Pointer to the game instance.
     * @param parent Pointer to the parent QObject, default is nullptr.
     */
    MyTCPClient(Game* gameInstance, QObject *parent = nullptr);

    /**
     * @brief Connects to a host using the provided IP and port.
     * @param ip The IP address of the host to connect to.
     * @param port The port of the host to connect to.
     */
    void connectToHost(QString ip, int port);

    /**
     * @brief Disconnects the client from the host.
     */
    void disconnect();

    /**
     * @brief Returns the current state of the TCP socket.
     * @return The state of the TCP socket.
     */
    QAbstractSocket::SocketState state();

    /**
     * @brief Checks if the client is currently connected.
     * @return True if connected, false otherwise.
     */
    bool isConnected();

    /**
     * @brief Attempts to reconnect to the host.
     */
    void tryReconnect();

signals:
    /**
     * @brief Signal emitted when the client successfully connects to the server.
     */
    void connected();

    /**
     * @brief Signal emitted when the client is disconnected from the server.
     */
    void disconnected();

    /**
     * @brief Signal emitted when the socket state changes.
     * @param state The new state of the socket.
     */
    void stateChanged(QAbstractSocket::SocketState);

private slots:

    /**
     * @brief Slot that handles changes in the socket state.
     * @param state The new socket state.
     */
    void socket_stateChanged(QAbstractSocket::SocketState);

private:
    QString _ip; ///< Stores the IP address of the connected server.
    int _port; ///< Stores the port of the connected server.

    /**
     * @brief Recursively attempts to reconnect to the server.
     * @param remainingAttempts The number of remaining attempts.
     */
    void attemptReconnect(int remainingAttempts);

};

#endif // MYTCPCLIENT_H
