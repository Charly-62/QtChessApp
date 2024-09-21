/**
 * @file netzwerk.h
 * @brief This file contains the declaration of the Netzwerk class, which manages network communication.
 */

#ifndef NETZWERK_H
#define NETZWERK_H

#include "game.h"

#include <QObject>
#include <QTcpSocket>

/**
 * @class Netzwerk
 * @brief Manages network communication between players in the chess game.
 */
class Netzwerk : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the Netzwerk class.
     * @param gameInstance Reference to the game instance for handling game moves.
     * @param parent Pointer to the parent QObject, default is nullptr.
     */
    Netzwerk(Game* gameInstance = nullptr, QObject *parent = nullptr);

    /**
     * @brief Destructor for the Netzwerk class.
     */
    virtual ~Netzwerk();

    /**
     * @brief Sends a move over the network.
     * @param moveInfo The information about the move being sent.
     */
    void sendMove(const MoveInfo&);

    /**
     * @brief Sends the response to a move.
     * @param status The status of the move (accepted, rejected, etc.).
     */
    void sendMoveResponse(quint8 status);

    /**
     * @brief Sends a message to start a game.
     * @param ServerStarts Indicates whether the server starts the game.
     */
    void sendGameStart(bool ServerStarts);

    /**
     * @brief Sends a response to the game start message.
     */
    void sendGameStartResponse();

    /**
     * @brief Sends a request to undo a move.
     */
    void sendUndo();

    /**
     * @brief Sends a response to an undo request.
     * @param accepted Indicates whether the undo request was accepted.
     */
    void sendUndoResponse(bool accepted);

    bool undoMovetmp = false; ///< Temporary flag for undo move state.

    /**
     * @brief Sends a chat message.
     * @param message The chat message to be sent.
     */
    void sendChatMsg(QString message);

    /**
     * @brief Sends the player's name to the opponent.
     * @param name The player's name.
     */
    void sendName(QString);

    /**
     * @brief Returns the opponent group number.
     * @return The opponent group number.
     */
    int getopponentgroup() {
        return opponentgroup;
    }


    /**
     * @brief Initializes the socket if it's not already initialized.
     */
    void initializeSocket();

    /**
     * @brief Receives a move from the network.
     * @param moveData The data received over the network containing move information.
     */
    void receiveMove();

protected:
    QTcpSocket* _socket = nullptr; ///< TCP socket used for network communication.
    QByteArray buffer; ///< Buffer to accumulate incoming data.

private:
    Game* gameInstance; ///< Reference to the game instance.
    int opponentgroup = 0; // Playing against this group
    void onSocketError(QAbstractSocket::SocketError socketError);

    /**
     * @brief processMessage Processes the received message
     * @param stream Received data
     */
    void processMessage(QDataStream& stream);

signals:

    /**
     * @brief Signal to log a message to the Netzwerk console.
     * @param message The message to log.
     */
    void logNetzwerkMsg(const QString& message); // Signal to log messages to the NetzwerkConsole

    /**
     * @brief Signal to log an in-game message.
     * @param message The message to log.
     */
    void logInGameMsg(const QString& message);

    /**
     * @brief Signal emitted when a move is received.
     * @param moveInfo Information about the move.
     */
    void moveReceived(MoveInfo moveInfo);

    /**
     * @brief Signal emitted when the game starts.
     * @param ServerStarts Indicates if the server starts the game.
     * @param groupNumber Group number of the opponent.
     */
    void gameStarted(bool ServerStarts, QString& groupNumber);

    /**
     * @brief Signal emitted when a move is rejected.
     */
    void moveRejected();

    /**
     * @brief Signal emitted when an undo move request is made.
     */
    void undoMove();

    /**
     * @brief Signal emitted when an undo move request is accepted.
     * @param accepted True if the undo request is accepted, false otherwise.
     */
    void undoAccepted(bool accepted);

    /**
     * @brief Signal emitted when the opponent's name is received.
     * @param oppName The opponent's name.
     */
    void opponentNameReceived(QString oppName);

    /**
     * @brief Signal emitted when a chat message is received.
     * @param message The chat message received.
     */
    void ChatMsgReceived(QString message);

};

#endif // NETZWERK_H
