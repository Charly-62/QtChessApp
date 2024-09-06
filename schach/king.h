/**
 * @file game.h
 * @brief This file contains the implementation of the king class, representing a king in chess.
 */

#ifndef KING_H
#define KING_H

#include "piece.h"

/**
 * @class king
 * @brief Represents a King piece in the chess game.
 */
class King : public Piece
{
public:
    /**
     * @brief Constructor for King.
     * @param isWhite Boolean value to set the color of the piece.
     * @param col Column position of the King on the board.
     * @param row Row position of the King on the board.
     */
    King(bool isWhite, int col, int row) {
        this->isWhite = isWhite;
        this->col = col;
        this->row = row;
    }

    /**
     * @brief Retrieves the possible moves for the King.
     * @return A vector of possible moves for the King.
     */
    std::vector<std::pair<int, int>> getPossibleMoves() const override {
        std::vector<std::pair<int, int>> moves;

        // Implement possible moves

        return moves;
    }
    QString getType() const override {
            return "king";
        }
};

#endif // KING_H
