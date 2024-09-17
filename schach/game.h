/**
 * @file game.h
 * @brief This file contains the declaration of the Game class which manages the chessboard and game logic.
 */

#ifndef GAME_H
#define GAME_H

#include "logik.h"
#include "piece.h"

#include <memory>
#include <QObject>
#include <QWidget>
#include <QTcpSocket>
#include <QDataStream>
#include <iostream>
#include <QString>
#include <QComboBox>
#include <QEvent>


class SchachApp;
class Netzwerk;

/**
 * @brief Struct containing information for each move.
 */
struct MoveInfo {

    int s_col = 0, s_row = 0, e_col = 0, e_row = 0;
    quint8 consequences = 0x00, promotion = 0x00;
    bool islegal = false;

    std::shared_ptr<Piece> capturedPiece = nullptr; // The piece that was captured, if any
    bool movedPieceHasMovedBefore = false;        // Whether the moving piece had moved before this move
    bool rookHasMovedBefore = false;              // In case of castling, whether the rook had moved before
    int lastMoveWasTwoSquarePawnMoveBefore = 8; // To restore en passant possibilities
    std::shared_ptr<Piece> pawnBeforePromotion = nullptr; // In case of promotion, the pawn before promotion

    // Additional info for castling
    int rookStartCol = -1; // For castling, the starting column of the rook
    int rookEndCol = -1;   // For castling, the ending column of the rook

    // For en passant
    std::shared_ptr<Piece> enPassantCapturedPawn = nullptr; // In case of en passant, the pawn that was captured

};

/**
 * @class Game
 * @brief Manages the state of the chess game.
 */
class Game : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Constructor for the Game class.
     * @param gui Pointer to the SchachApp (GUI) object.
     * @param parent Pointer to the parent QObject, default is nullptr.
     */
    Game(SchachApp* gui, QObject* parent = nullptr);

    /**
     * @brief Destructor for the Game class.
     */
    ~Game();

    /// Logik instance
    Logik logikInstance;

    /**
     * @brief Updates the board by making a move.
     * @param s_col Starting column.
     * @param s_row Starting row.
     * @param e_col Ending column.
     * @param e_row Ending row.
     */
    void updateBoard(int s_col, int s_row, int e_col, int e_row);

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
     * @brief Checks if square is attacked
     * @param col Column of the piece.
     * @param row Row of the piece.
     * @param currentPlayerIsWhite used to check only attacks from opposing team
     * @return Bool true if square is attacked.
     */
    bool isSquareAttacked(int col, int row, bool currentPlayerIsWhite) const;

    /**
     * @brief Finds the position of the King on the board for the specified team.
     *
     * @param isWhite True if searching for the white king, false for the black king.
     * @return A pair of integers representing the (column, row) position of the King.
     *         Returns (-1, -1) if the King is not found (invalid state).
     */
    std::pair<int, int> findKing(bool isWhite) const;

    /**
     * @brief Checks if it is white's turn.
     * @return True if it is white's turn, otherwise false.
     */
    bool getWhiteTurn(){
        return whiteTurn;
    }

    std::shared_ptr<Piece> board[8][8]; ///< 2D array representing the chessboard.

    /**
     * @brief Checks if the King is in check.
     * @param isWhite True to check white's King, false for black's King.
     * @return True if the specified King is in check, otherwise false.
     */
    bool getCheck(bool isWhite) const{
        if(isWhite){
            return whiteKingChecked;
        }
        return blackKingChecked;
    }


    /**
     * @brief Sets whether the King is in check.
     * @param check True if the King is in check, otherwise false.
     * @param isWhite True to set white's King, false for black's King.
     */
    void setCheck(bool check, bool isWhite) {
        if(isWhite){
            whiteKingChecked = check;
        }else{
            blackKingChecked = check;
        }
    }

    /**
     * @brief Clones the current game state.
     * @return A pointer to the cloned Game instance.
     */
    Game* clone() const;

    std::vector<MoveInfo> moveHistory; ///< Stack to track the history of moves.

    /**
     * @brief Undoes the specified move.
     * @param moveInfo Information about the move to undo.
     */
    void undoMove(MoveInfo moveInfo);

    int lastMoveWasTwoSquarePawnMove = 8; ///< Indicates the column of the last pawn two-square move, 8 means no such move.

    /**
     * @brief Switches the turn to the other player.
     */
    void switchTurn();

    /**
     * @brief Switches the turn and sets whether it is white's turn.
     * @param whiteTurn True if it is white's turn, otherwise false.
     */
    void switchTurn(bool);

    int rowPawnPromotion; ///< Row where a pawn can promote.

    bool isCheckmate = false; ///< Flag to indicate if the game is in checkmate.

    /**
     * @brief Updates the status of whether the King is in check.
     */
    void updateCheckStatus();

private:

    bool whiteTurn; ///< Indicates if it is white's turn.
    bool whiteKingChecked; ///< Indicates if white's King is in check.
    bool blackKingChecked; ///< Indicates if black's King is in check.
    SchachApp* gui; ///< Pointer to the GUI instance.

    /**
     * @brief Initializes the chessboard with the pieces in their starting positions.
     */
    void initBoard();

signals:
    /**
     * @brief Signal emitted when a piece is captured.
     * @param capturedPiece The piece that was captured.
     */
    void pieceCaptured(std::shared_ptr<Piece> capturedPiece);

    /**
     * @brief isEnPassant Emitted when in passant move
     * @param score
     * @param isWhite
     */
    void isEnPassant(int score, bool isWhite);

    void pawnPromoted(int pieceValue, bool isWhite);

};

#endif // GAME_H
