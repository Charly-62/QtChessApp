/**
 * @file game.h
 * @brief This file contains the implementation of the queen class, representing a queen in chess.
 */

#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

/**
 * @class queen
 * @brief Represents a Queen piece in the chess game.
 */
class Queen : public Piece
{
public:
    /**
     * @brief Constructor for Queen.
     * @param isWhite Boolean value to set the color of the piece.
     * @param col Column position of the Queen on the board.
     * @param row Row position of the Queen on the board.
     */
    Queen(bool isWhite, int col, int row) {
        this->isWhite = isWhite;
        this->col = col;
        this->row = row;
    }

    /**
     * @brief Retrieves the possible moves for the Queen.
     * @return A vector of possible moves for the Queen.
     */
    std::vector<std::pair<int, int>> getPossibleMoves() const override {
        std::vector<std::pair<int, int>> moves;

        // Implement possible moves

        return moves;
    }
    QString getType() const override {
            return "queen"
                   "";
        }
};

#endif // QUEEN_H
