#include "king.h"
#include "game.h"

std::vector<std::pair<int, int>> King::getPossibleMoves(const Game* game) const {
    std::vector<std::pair<int, int>> moves;

    // Possible moves for a King (one square in any direction)
    std::vector<std::pair<int, int>> potentialMoves = {
        {col + 1, row},   // Move right
        {col - 1, row},   // Move left
        {col, row + 1},   // Move up
        {col, row - 1},   // Move down
        {col + 1, row + 1}, // Move up-right
        {col - 1, row + 1}, // Move up-left
        {col + 1, row - 1}, // Move down-right
        {col - 1, row - 1}  // Move down-left
    };

    for (const auto& move : potentialMoves) {
        int newCol = move.first;
        int newRow = move.second;

        // Check if the move is within the bounds of the board (0 to 7)
        if (newCol >= 0 && newCol < 8 && newRow >= 0 && newRow < 8) {
            std::shared_ptr<Piece> pieceAtNewPosition = game->getPieceAt(newCol, newRow);
            if (pieceAtNewPosition == nullptr || pieceAtNewPosition->checkIfWhite() != isWhite) {
                moves.push_back(move);  // Add the move if it's empty or occupied by an opponent piece
            }
        }
    }

    // // Castling logic
     std::shared_ptr<Piece> thisKing = game->getPieceAt(col, row);
     if (!thisKing->checkMoved() && !game->isSquareAttacked(col, row, isWhite)) {  // King hasn't moved and is not in check

    //     // Kingside castling (towards the right rook)
    //     if (col == 4 && ((isWhite && row == 0) || (!isWhite && row == 7))) {  // King is in starting position
    //         // Check if the right rook is in place and hasn't moved
    //         std::shared_ptr<Piece> rightRook = game->getPieceAt(7, row);
    //         if (rightRook && rightRook->getType() == "rook" && !rightRook->checkMoved() && rightRook->checkIfWhite() == isWhite) {
    //             // Check if the squares between the king and the rook are empty
    //             if (game->getPieceAt(5, row) == nullptr && game->getPieceAt(6, row) == nullptr) {
    //                 // Check if the king is not moving through or into check
    //                 if (!game->isSquareAttacked(4, row, !isWhite) &&
    //                     !game->isSquareAttacked(5, row, !isWhite) &&
    //                     !game->isSquareAttacked(6, row, !isWhite)) {
    //                     moves.push_back({6, row});  // Kingside castling move
    //                 }
    //             }
    //         }
    //     }

    //     // Queenside castling (towards the left rook)
    //     if (col == 4 && ((isWhite && row == 0) || (!isWhite && row == 7))) {  // King is in starting position
    //         // Check if the left rook is in place and hasn't moved
    //         std::shared_ptr<Piece> leftRook = game->getPieceAt(0, row);
    //         if (leftRook && leftRook->getType() == "rook" && !leftRook->checkMoved() && leftRook->checkIfWhite() == isWhite) {
    //             // Check if the squares between the king and the rook are empty
    //             if (game->getPieceAt(1, row) == nullptr && game->getPieceAt(2, row) == nullptr && game->getPieceAt(3, row) == nullptr) {
    //                 // Check if the king is not moving through or into check
    //                 if (!game->isSquareAttacked(4, row, !isWhite) &&
    //                     !game->isSquareAttacked(3, row, !isWhite) &&
    //                     !game->isSquareAttacked(2, row, !isWhite)) {
    //                     moves.push_back({2, row});  // Queenside castling move
    //                 }
    //             }
    //         }
    //     }
    //}
     }

    return moves;
}
