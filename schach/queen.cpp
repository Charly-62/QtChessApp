#include "queen.h"
#include "game.h"

std::vector<std::pair<int, int>> Queen::getPossibleMoves(const Game* game) const {
    std::vector<std::pair<int, int>> moves;

    // Directions for horizontal, vertical, and diagonal moves
    std::vector<std::pair<int, int>> directions = {
        {1, 0}, {0, 1}, {-1, 0}, {0, -1},  // Horizontal and vertical
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1} // Diagonals
    };

    for (const auto& direction : directions) {
        int x = col;
        int y = row;

        while (true) {
            x += direction.first;
            y += direction.second;

            // Check if the new position is out of bounds
            if (x < 0 || x >= 8 || y < 0 || y >= 8) {
                break;
            }

            std::shared_ptr<Piece> piece = game->getPieceAt(x, y);
            if (piece == nullptr) {
                moves.push_back({x, y});
            } else {
                if (piece->checkIfWhite() != isWhite) {
                    moves.push_back({x, y});  // Capture the opponent's piece
                }
                break;  // Stop moving in this direction if a piece is found
            }
        }
    }

    return moves;
}
