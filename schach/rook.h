/**
 * @file game.h
 * @brief This file contains the implementation of the rook class, representing a rook in chess.
 */

#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

/**
 * @class rook
 * @brief Represents a Rook piece in the chess game.
 */
class Rook : public Piece
{
public:
    /**
     * @brief Constructor for Rook.
     * @param isWhite Boolean value to set the color of the piece.
     * @param col Column position of the Rook on the board.
     * @param row Row position of the Rook on the board.
     */
    Rook(bool isWhite, int col, int row) {
        this->isWhite = isWhite;
        this->col = col;
        this->row = row;
    }

    /**
     * @brief Retrieves the possible moves for the Rook.
     * @return A vector of possible moves for the Rook.
     */
    std::vector<std::pair<int, int>> getPossibleMoves() const override {
        std::vector<std::pair<int, int>> moves;

        // Rook moves vertically or horizontally any number of spaces
        for (int i = 0; i < 8; ++i) {
            if (i != col) moves.push_back({i, row}); // Horizontal
            if (i != row) moves.push_back({col, i}); // Vertical
        }

        return moves;
    }
};

#endif // ROOK_H
