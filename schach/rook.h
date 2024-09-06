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

//        // Check horizontal (left and right)
//            for (int i = col + 1; i < 8; ++i) {  // Move to the right
//                if (board.isOccupied(i, row)) {
//                    if (board.getPiece(i, row)->isWhite() != this->isWhite) {
//                        moves.push_back({i, row});  // Capture the enemy piece
//                    }
//                    break;  // Stop moving if a piece is found
//                }
//                moves.push_back({i, row});
//            }

//            for (int i = col - 1; i >= 0; --i) {  // Move to the left
//                if (board.isOccupied(i, row)) {
//                    if (board.getPiece(i, row)->isWhite() != this->isWhite) {
//                        moves.push_back({i, row});  // Capture the enemy piece
//                    }
//                    break;
//                }
//                moves.push_back({i, row});
//            }

//            // Check vertical (up and down)
//            for (int i = row + 1; i < 8; ++i) {  // Move upwards
//                if (board.isOccupied(col, i)) {
//                    if (board.getPiece(col, i)->isWhite() != this->isWhite) {
//                        moves.push_back({col, i});  // Capture the enemy piece
//                    }
//                    break;
//                }
//                moves.push_back({col, i});
//            }

//            for (int i = row - 1; i >= 0; --i) {  // Move downwards
//                if (board.isOccupied(col, i)) {
//                    if (board.getPiece(col, i)->isWhite() != this->isWhite) {
//                        moves.push_back({col, i});  // Capture the enemy piece
//                    }
//                    break;
//                }
//                moves.push_back({col, i});
//            }


        return moves;
    }
    QString getType() const override {
            return "rook";
        }
};

#endif // ROOK_H
