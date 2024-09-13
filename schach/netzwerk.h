/**
 * @file game.h
 * @brief This file contains the declaration of the netzwerk class which manages network communication.
 */

#ifndef NETZWERK_H
#define NETZWERK_H

#include <QObject>
#include <QTcpSocket>

#include "game.h"

/**
 * @class netzwerk
 * @brief Manages network communication between players in the chess game.
 */
class Netzwerk : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the netzwerk class.
     * @param gameInstance Reference to the game instance for handling game moves.
     */
    Netzwerk(Game* gameInstance = nullptr, QObject *parent = nullptr);

    virtual ~Netzwerk();

    /**
     * @brief Sends a move over the network.
     * @param s_col The starting column of the move.
     * @param s_row The starting row of the move.
     * @param e_col The ending column of the move.
     * @param e_row The ending row of the move.
     */
    void sendMove(const MoveInfo&);
    void sendMoveResponse(quint8 status);

    void sendGameStart(bool ServerStarts);
    void sendGameStartResponse();

    /**
     * @brief Receives a move from the network.
     * @param moveData The data received over the network containing move information.
     */
    void receiveMove();

    /**
     * @brief Initializes the socket if it's not already done
     */
    void initializeSocket();


protected:
    QTcpSocket* _socket = nullptr;

private:
    Game* gameInstance; ///< Reference to the game instance.

signals:
    void logMessage(const QString& message); // Signal to log messages to the NetzwerkConsole
    void moveReceived(MoveInfo moveInfo);
    void gameStarted(bool ServerStarts, QString& groupNumber);

};

#endif // NETZWERK_H
