/**
 * @file game.h
 * @brief This file contains the declaration of the piece class and its derived classes representing chess pieces.
 */

#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <utility>

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
     * @brief Retrieves the possible moves for the chess piece. (virtual)
     * @return A vector of possible moves for the piece.
     */
    virtual std::vector<std::pair<int, int>> getPossibleMoves() const = 0;

protected:
    int col,        ///< Column position of the piece on the board.
        row;        ///< Row position of the piece on the board.
    bool isWhite;   ///< Boolean indicating if the piece is white or black.
};

#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"

#endif // PIECE_H
