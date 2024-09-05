/**
 * @file game.h
 * @brief This file contains the implementation of the game class which manages the chessboard and some game logic.
 */

#ifndef GAME_H
#define GAME_H

#include "logik.h"
#include "piece.h"
#include "qtypes.h"
#include <memory>

class SchachApp;
class Netzwerk;

/**
 * @brief Struct with the informations for each move
 */
struct MoveInfo {

    int s_col, s_row, e_col, e_row;
    quint8 consequences, promotion;

};

/**
 * @class game
 * @brief Manages the state of the chess game.
 */
class Game
{
public:

        /**
     * @brief Constructor for the game instance.
     * @param gui Pointer to the SchachApp (GUI) object.
     * @param netzwerkInsance Pointer to the Netzwerk object.
     */
    explicit Game(SchachApp* gui, Netzwerk* netzwerkInstance);

    /**
     * @brief Destructor for the game class.
     */
    ~Game();

    /// Logik instance
    Logik logikInstance;

    /**
     * @brief Attempts to move a piece on the chessboard.
     * @param s_col Starting column of the piece.
     * @param s_row Starting row of the piece.
     * @param e_col Ending column of the piece.
     * @param e_row Ending row of the piece.
     * @return True if the move is successful, otherwise false. [TODO]: return error type if false (we also have to send it via TCP/IP)
     */
    MoveInfo tryMove(int s_col, int s_row, int e_col, int e_row);

    /**
     * @brief Retrieves the piece at the specified board position.
     * @param col Column of the piece.
     * @param row Row of the piece.
     * @return A shared pointer to the piece at the given position.
     */
    std::shared_ptr<Piece> getPieceAt(int col, int row) const;

    /**
     * @brief Gets the info about promotion to send it via TCP/IP
     * [TODO] Implementation and define parameters
     * @return Info about promotion to send it via TCP/IP
     */
    quint8 getPawnPromotion();

private:
    std::shared_ptr<Piece> board[8][8];
    bool whiteTurn;
    SchachApp* gui;
    Netzwerk* netzwerkInstance;

    /**
     * @brief Initializes the chessboard with the pieces in their starting positions.
     */
    void initBoard();

    /**
     * @brief updateBoard Makes a move on the board
     * @param s_col starting col
     * @param s_row starting row
     * @param e_col ending col
     * @param e_row ending row
     */
    void updateBoard(int s_col, int s_row, int e_col, int e_row);

};

#endif // GAME_H
