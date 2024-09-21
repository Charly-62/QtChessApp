/**
 * @file rook.h
 * @brief This file contains the implementation of the rook class, representing a rook in chess.
 */

#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
class Game;

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

    std::shared_ptr<Piece> clone() const override {
            return std::make_shared<Rook>(*this); // Correctly implement cloning
    }

    /**
     * @brief Retrieves the possible moves for the Rook.
     * @return A vector of possible moves for the Rook.
     */
    std::vector<std::pair<int, int>> getPossibleMoves(const Game* game) const override;

    QString getType() const override {
            return "rook";
        }
};

#endif // ROOK_H
