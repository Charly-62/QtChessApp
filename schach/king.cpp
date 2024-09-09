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

    return moves;
}
