#include "knight.h"
#include "game.h"

std::vector<std::pair<int, int>> Knight::getPossibleMoves(const Game* game) const {
    std::vector<std::pair<int, int>> moves;

    // Knight moves in an L-shape
    std::vector<std::pair<int, int>> potentialMoves = {
        {col + 2, row + 1},
        {col + 2, row - 1},
        {col - 2, row + 1},
        {col - 2, row - 1},
        {col + 1, row + 2},
        {col - 1, row + 2},
        {col + 1, row - 2},
        {col - 1, row - 2}
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
