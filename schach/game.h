/**
 * @file game.h
 * @brief This file contains the implementation of the game class which manages the chessboard and some game logic.
 */

#ifndef GAME_H
#define GAME_H

#include "piece.h"
#include <memory>

class SchachApp;
class netzwerk;

/**
 * @class game
 * @brief Manages the state of the chess game.
 */
class game
{
public:

        /**
     * @brief Constructor for the game instance.
     * @param gui Pointer to the SchachApp (GUI) object.
     * @param netzwerk Pointer to the Netzwerk object.
     */
    game(SchachApp* gui, netzwerk* netzwerk);

    /**
     * @brief Destructor for the game class.
     */
    ~game();

    /**
     * @brief Attempts to move a piece on the chessboard.
     * @param s_col Starting column of the piece.
     * @param s_row Starting row of the piece.
     * @param e_col Ending column of the piece.
     * @param e_row Ending row of the piece.
     * @return True if the move is successful, otherwise false. [TODO]: return error type if false (we also have to send it via TCP/IP)
     */
    bool tryMove(int s_col, int s_row, int e_col, int e_row);

    /**
     * @brief Retrieves the piece at the specified board position.
     * @param col Column of the piece.
     * @param row Row of the piece.
     * @return A shared pointer to the piece at the given position.
     */
    std::shared_ptr<piece> getPieceAt(int col, int row) const;

private:
    std::shared_ptr<piece> board[8][8];
    bool whiteTurn;
    SchachApp* gui;
    netzwerk* netzwerk;

    /**
     * @brief Initializes the chessboard with the pieces in their starting positions.
     */
    void initBoard();

};

#endif // GAME_H
