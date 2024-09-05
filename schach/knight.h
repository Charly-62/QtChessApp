/**
 * @file game.h
 * @brief This file contains the implementation of the knight class, representing a knight in chess.
 */

#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

/**
 * @class knight
 * @brief Represents a Knight piece in the chess game.
 */
class Knight : public Piece
{
public:
    /**
     * @brief Constructor for Knight.
     * @param isWhite Boolean value to set the color of the piece.
     * @param col Column position of the Knight on the board.
     * @param row Row position of the Knight on the board.
     */
    Knight(bool isWhite, int col, int row) {
        this->isWhite = isWhite;
        this->col = col;
        this->row = row;
    }

    /**
     * @brief Retrieves the possible moves for the Knight.
     * @return A vector of possible moves for the Knight.
     */
    std::vector<std::pair<int, int>> getPossibleMoves() const override {
        std::vector<std::pair<int, int>> moves;

        // Knight moves in an L-shape
        moves.push_back({col + 2, row + 1});
        moves.push_back({col + 2, row - 1});
        moves.push_back({col - 2, row + 1});
        moves.push_back({col - 2, row - 1});
        moves.push_back({col + 1, row + 2});
        moves.push_back({col - 1, row + 2});
        moves.push_back({col + 1, row - 2});
        moves.push_back({col - 1, row - 2});

        return moves;
    }
};

#endif // KNIGHT_H
