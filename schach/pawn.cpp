#include "pawn.h"
#include "game.h"

/**
 * @brief Retrieves the possible moves for the Pawn.
 * @param game Pointer to the Game object for checking the board state.
 * @return A vector of possible moves for the Pawn.
 */
std::vector<std::pair<int, int>> Pawn::getPossibleMoves(const Game* game) const {
    std::vector<std::pair<int, int>> moves;

    // Determine move direction based on the color of the Pawn
    int direction = isWhite ? 1 : -1;

    // Move one square forward
    int newRow = row + direction;
    if (newRow >= 0 && newRow < 8) {
        // Check if the square in front is empty
        if (game->getPieceAt(col, newRow) == nullptr) {
            moves.push_back({col, newRow});

            // Move two squares forward if at the starting position
            if ((isWhite && row == 1) || (!isWhite && row == 6)) {
                newRow += direction;
                if (newRow >= 0 && newRow < 8 && game->getPieceAt(col, newRow) == nullptr) {
                    moves.push_back({col, newRow});
                }
            }
        }
    }

    // Capture opponents diagonally
    int captureRow = row + direction;
    if (captureRow >= 0 && captureRow < 8) {
        if (col > 0) {  // Check left diagonal
            std::shared_ptr<Piece> leftDiagonal = game->getPieceAt(col - 1, captureRow);
            if (leftDiagonal != nullptr && leftDiagonal->checkIfWhite() != isWhite) {
                moves.push_back({col - 1, captureRow});
            }
        }

        if (col < 7) {  // Check right diagonal
            std::shared_ptr<Piece> rightDiagonal = game->getPieceAt(col + 1, captureRow);
            if (rightDiagonal != nullptr && rightDiagonal->checkIfWhite() != isWhite) {
                moves.push_back({col + 1, captureRow});
            }
        }
    }

    return moves;
}


