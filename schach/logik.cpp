/**
 * @file logik.cpp
 * @brief Implements the game logik.
 */

#include "logik.h"
#include "game.h"
#include "piece.h"
#include <memory>

bool Logik::isLegal(Game* Game, int s_col, int s_row, int e_col, int e_row) const{
    // Step 1: Check if the source and destination are within bounds (0 to 7)
    if (s_col < 0 || s_col >= 8 || s_row < 0 || s_row >= 8 ||
        e_col < 0 || e_col >= 8 || e_row < 0 || e_row >= 8) {
        return false;  // Move is out of bounds
    }

    // Get pointer to the moving piece
    std::shared_ptr<Piece> movingPiece = Game->getPieceAt(s_col, s_row);

    // Step 2: Check if there is a piece at the source position
    if (!movingPiece) {
        return false;  // No piece to move
    }

    // Step 3: Get the possible moves for the piece and check if the destination is valid
    std::vector<std::pair<int, int>> possibleMoves = movingPiece->getPossibleMoves();
    bool validMove = false;
    for (const auto& move : possibleMoves) {
        if (move.first == e_col && move.second == e_row) {
            validMove = true;
            break;
        }
    }

    // If the move is not valid, return false
    if (!validMove) {
        return false;  // Invalid move for this piece
    }

    return true;
}

bool Logik::isCaptureMove(Game* Game, int s_col, int s_row, int e_col, int e_row) const{
    std::shared_ptr<Piece> endPiece = Game->getPieceAt(s_col, s_row);

    // [TODO] Before this, check if endPiece is from your team
    if(endPiece != nullptr)
        return true;

    return false;
}


bool Logik::isCheckmate(Game* Game, int e_col, int e_row) const{

    return false; // [TODO] Implement
}


bool Logik::isCastlingMove(Game* Game, int s_col, int s_row, int e_col, int e_row) const{

    return false; // [TODO] Implement
}


bool Logik::isPawnPromotion(Game* Game, int e_col, int e_row) const{

    return false; // [TODO] Implement
}

