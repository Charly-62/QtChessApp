#include "rook.h"
#include "game.h"

#include <memory>

std::vector<std::pair<int, int>> Rook::getPossibleMoves(const Game* game) const {
    std::vector<std::pair<int, int>> moves;

    // Check horizontal (left and right)
    for (int i = col + 1; i < 8; ++i) {  // Move to the right
        if (game->getPieceAt(i, row) != nullptr) {
            if (game->getPieceAt(i, row)->checkIfWhite() != this->isWhite) {
                moves.push_back({i, row});  // Capture the enemy piece
            }
            break;  // Stop moving if a piece is found
        }
        moves.push_back({i, row});
    }

    for (int i = col - 1; i >= 0; --i) {  // Move to the left
        if (game->getPieceAt(i, row) != nullptr) {
            if (game->getPieceAt(i, row)->checkIfWhite() != this->isWhite) {
                moves.push_back({i, row});  // Capture the enemy piece
            }
            break;
        }
        moves.push_back({i, row});
    }

    // Check vertical (up and down)
    for (int i = row + 1; i < 8; ++i) {  // Move upwards
        if (game->getPieceAt(col, i) != nullptr) {
            if (game->getPieceAt(col, i)->checkIfWhite() != this->isWhite) {
                moves.push_back({col, i});  // Capture the enemy piece
            }
            break;
        }
        moves.push_back({col, i});
    }

    for (int i = row - 1; i >= 0; --i) {  // Move downwards
        if (game->getPieceAt(col, i) != nullptr) {
            if (game->getPieceAt(col, i)->checkIfWhite() != this->isWhite) {
                moves.push_back({col, i});  // Capture the enemy piece
            }
            break;
        }
        moves.push_back({col, i});
    }

    return moves;
}
