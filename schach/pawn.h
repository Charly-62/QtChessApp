/**
 * @file pawn.h
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

    std::shared_ptr<Piece> clone() const override {
            return std::make_shared<Pawn>(*this); // Correctly implement cloning
    }

    /**
     * @brief Retrieves the possible moves for the Pawn.
     * @return A vector of possible moves for the Pawn.
     */
    std::vector<std::pair<int, int>> getPossibleMoves(const Game* game) const override;

    QString getType() const override {
                return "pawn";
    }

};

#endif // PAWN_H
