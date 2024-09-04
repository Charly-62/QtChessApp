/**
 * @file game.h
 * @brief This file contains the declaration of the netzwerk class which manages network communication.
 */

#ifndef NETZWERK_H
#define NETZWERK_H

#include <QTcpSocket>

#include "game.h"

/**
 * @class netzwerk
 * @brief Manages network communication between players in the chess game.
 */
class netzwerk
{
public:
    /**
     * @brief Constructor for the netzwerk class.
     * @param game Reference to the game instance for handling game moves.
     */
    netzwerk(game* game);

    /**
     * @brief Sends a move over the network.
     * @param s_col The starting column of the move.
     * @param s_row The starting row of the move.
     * @param e_col The ending column of the move.
     * @param e_row The ending row of the move.
     */
    void sendMove(int s_col, int s_row, int e_col, int e_row);

    /**
     * @brief Receives a move from the network.
     * @param moveData The data received over the network containing move information.
     */
    void receiveMove(QByteArray moveData);

    /**
     * @brief Assigns a game instance to the network handler. Just used for initialization.
     * @param game Reference to the game instance.
     */
    void setGame(game* game);

private:
    game* game; /// Reference to the game instance.

};

#endif // NETZWERK_H
