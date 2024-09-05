/**
 * @file game.h
 * @brief This file contains the implementation of the pawn class, representing a pawn in chess.
 */

#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

/**
 * @class pawn
 * @brief Represents a Pawn piece in the chess game.
 */
class Pawn : public Piece
{
public:
    /**
     * @brief Constructor for Pawn.
     * @param isWhite Boolean value to set the color of the piece.
     * @param col Column position of the Pawn on the board.
     * @param row Row position of the Pawn on the board.
     */
    Pawn(bool isWhite, int col, int row) {
        this->isWhite = isWhite;
        this->col = col;
        this->row = row;
    }

    /**
     * @brief Retrieves the possible moves for the Pawn.
     * @return A vector of possible moves for the Pawn.
     */
    std::vector<std::pair<int, int>> getPossibleMoves() const override {
        std::vector<std::pair<int, int>> moves;

        /// Move direction of the pawn (depends on team)
        int direction = isWhite ? -1 : 1;

        /// Move one square forward
        moves.push_back({col, row + direction});

        /// Move two squares forward if at the starting position
        if ((isWhite && row == 6) || (!isWhite && row == 1)) {
            moves.push_back({col, row + 2 * direction});
        }

        return moves;
    }



};

#endif // PAWN_H
