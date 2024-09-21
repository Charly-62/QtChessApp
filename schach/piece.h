/**
 * @file piece.h
 * @brief This file contains the declaration of the piece class and its derived classes representing chess pieces.
 */

#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <utility>
#include <QString>
#include <memory>

class Game;

/**
 * @class piece
 * @brief Abstract base class representing a generic chess piece.
 */
class Piece
{
public:
    /**
     * @brief Virtual destructor for piece.
     */
    virtual ~Piece() {}

    /**
     * @brief Retrieves the possible moves for the chess piece.
     * @param game Pointer to the current game instance to assess possible moves.
     * @return A vector of pairs representing possible (row, column) moves for the piece.
     */
    virtual std::vector<std::pair<int, int>> getPossibleMoves(const Game* game) const = 0;

    /**
     * @brief Checks if the piece is white.
     * @return True if the piece is white, false if it's black.
     */
    bool checkIfWhite(){return isWhite;}

    /**
     * @brief Sets the position of the piece on the board.
     * @param newRow The new row position.
     * @param newCol The new column position.
     */
    void setPosition(int newRow, int newCol){row=newRow; col=newCol;}

    /**
     * @brief Checks if the piece has moved (used for castling logic).
     * @return True if the piece has moved, false otherwise.
     */
    bool checkMoved() const{return hasMoved;}

    /**
     * @brief Sets whether the piece has moved (used for castling logic).
     * @param movedPieceHasMovedBefore True if the piece has moved before, otherwise false.
     */
    void setMoved(bool movedPieceHasMovedBefore){
        hasMoved = movedPieceHasMovedBefore;
    }


    /**
     * @brief Returns the type of the chess piece as a QString.
     * @return The type of the chess piece (e.g., "Pawn", "Knight", etc.).
     */
    virtual QString getType() const = 0;

    /**
     * @brief Clones the piece, creating a deep copy.
     * @return A shared pointer to the cloned piece.
     */
    virtual std::shared_ptr<Piece> clone() const = 0; // Pure virtual function for cloning

protected:
    int col,        ///< Column position of the piece on the board.
        row;        ///< Row position of the piece on the board.
    bool isWhite;   ///< Boolean indicating if the piece is white or black.
    bool hasMoved = false; ///< Boolean if Piece has moved. Used for Castling
};

#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"

#endif // PIECE_H
