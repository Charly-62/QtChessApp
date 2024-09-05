/**
 * @file bishop.h
 * @brief This file contains the implementation of the bishop class, representing a bishop in chess.
 */

#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

/**
 * @class bishop
 * @brief Represents a Bishop piece in the chess game.
 */
class Bishop : public Piece
{
public:
    /**
     * @brief Constructor for Bishop.
     * @param isWhite Boolean value to set the color of the piece.
     * @param col Column position of the Bishop on the board.
     * @param row Row position of the Bishop on the board.
     */
    Bishop(bool isWhite, int col, int row) {
        this->isWhite = isWhite;
        this->col = col;
        this->row = row;
    }

    /**
     * @brief Retrieves the possible moves for the Bishop.
     * @return A vector of possible moves for the Bishop.
     */
    std::vector<std::pair<int, int>> getPossibleMoves() const override {
        std::vector<std::pair<int, int>> moves;

        // Implement possible moves

        return moves;
    }
};

#endif // BISHOP_H
