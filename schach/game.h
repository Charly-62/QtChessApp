/**
 * @file game.h
 * @brief This file contains the implementation of the game class which manages the chessboard and some game logic.
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


class SchachApp;
class Netzwerk;

/**
 * @brief Struct with the informations for each move
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
 * @class game
 * @brief Manages the state of the chess game.
 */
class Game : public QObject
{
    Q_OBJECT
public:

     /**
     * @brief Constructor for the game instance.
     * @param gui Pointer to the SchachApp (GUI) object.
     * @param netzwerkInsance Pointer to the Netzwerk object.
     */
    Game(SchachApp* gui, QObject* parent = nullptr);

    /**
     * @brief Destructor for the game class.
     */
    ~Game();

    /// Logik instance
    Logik logikInstance;

    /**
     * @brief updateBoard Makes a move on the board
     * @param s_col starting col
     * @param s_row starting row
     * @param e_col ending col
     * @param e_row ending row
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

    bool getWhiteTurn(){
        return whiteTurn;
    }

    std::shared_ptr<Piece> board[8][8];

    bool getCheck(bool isWhite) const{
        if(isWhite){
            return whiteKingChecked;
        }
        return blackKingChecked;
    }

    void setCheck(bool check, bool isWhite) {
        if(isWhite){
            whiteKingChecked = check;
        }else{
            blackKingChecked = check;
        }
    }

    Game* clone() const;

    std::vector<MoveInfo> moveHistory; // Stack to keep track of move history
    void undoMove(MoveInfo moveInfo);

    //the int value is the column of lastMoveWasTwoSquarePawnMove // 8 means lastMoveWasTwoSquarePawnMove is false
    int lastMoveWasTwoSquarePawnMove = 8;
    void switchTurn();
    void switchTurn(bool);
    int rowPawnPromotion;

 //   bool pawnPromotionCompleted ;

private:

    bool whiteTurn;
    bool whiteKingChecked;
    bool blackKingChecked;
    SchachApp* gui;


    /**
     * @brief Initializes the chessboard with the pieces in their starting positions.
     */
    void initBoard();

};

#endif // GAME_H
