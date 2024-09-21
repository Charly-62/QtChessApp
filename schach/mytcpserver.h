/**
 * @file mytcpserver.h
 * @brief This file contains the declaration of the server class.
 */

#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include "netzwerk.h"

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

/**
 * @class MyTCPServer
 * @brief Handles the server-side TCP communication for the chess game.
 *
 * This class manages accepting client connections, handling disconnections,
 * and managing the TCP socket state for the server.
 */
class MyTCPServer : public Netzwerk
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the MyTCPServer class.
     * @param gameInstance Pointer to the game instance.
     * @param parent Pointer to the parent QObject, default is nullptr.
     */
    explicit MyTCPServer(Game* gameInstance, QObject *parent = nullptr);

    /**
     * @brief Destructor for the MyTCPServer class.
     */
    ~MyTCPServer();

    /**
     * @brief Starts the server listening on the specified port.
     * @param port The port on which the server should listen.
     */
    void startListening(int port);

    /**
     * @brief Stops the server from listening for client connections.
     */
    void stopListening();

    /**
     * @brief Checks if the server is currently listening for connections.
     * @return True if the server is listening, false otherwise.
     */
    bool isListening();

signals:

    /**
     * @brief Signal emitted when a client's connection state changes (connect/disconnect).
     * @param clientInfo Information about the client connection or disconnection.
     */
    void clientStateChanged(QString clientInfo); // Signal for client connection/disconnection UI updates


    /**
     * @brief Signal emitted when a client successfully connects to the server.
     */
    void serverStatus(QString status); // Signal for server status UI updates

    /**
     * @brief Signal emitted when a client successfully connects to the server.
     */
    void client_Connected();

    /**
     * @brief Signal emitted when a client disconnects from the server.
     */
    void client_Disconnected();

private slots:
    /**
     * @brief Slot called when a client is attempting to connect.
     */
    void onClientConnecting();

    /**
     * @brief Slot called when a client disconnects.
     */
    void onClientDisconnected();

private:
    QTcpServer* server; ///< Pointer to the QTcpServer instance for handling incoming connections.
};

#endif // MYTCPSERVER_H
