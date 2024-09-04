/**
 * @file game.cpp
 * @brief This file contains the implementation of the game class which manages the chessboard and some game logic.
 */

#include "game.h"
#include "piece.h"

game::game(class SchachApp* gui, class netzwerk* netzwerkInstance)
    : whiteTurn(true), gui(gui), netzwerkInstance(netzwerkInstance) {
    initBoard();
}


game::~game() {}


void game::initBoard() {
    // Initialize white pieces
    board[0][0] = std::make_shared<rook> (true, 0, 0);
    board[0][1] = std::make_shared<knight> (true, 1, 0);
    board[0][2] = std::make_shared<bishop> (true, 2, 0);
    board[0][3] = std::make_shared<queen> (true, 3, 0);
    board[0][4] = std::make_shared<king> (true, 4, 0);
    board[0][5] = std::make_shared<bishop> (true, 5, 0);
    board[0][6] = std::make_shared<knight> (true, 6, 0);
    board[0][7] = std::make_shared<rook> (true, 7, 0);

    // Initialize black pieces
    board[7][0] = std::make_shared<rook> (false, 0, 7);
    board[7][1] = std::make_shared<knight> (false, 1, 7);
    board[7][2] = std::make_shared<bishop> (false, 2, 7);
    board[7][3] = std::make_shared<queen> (false, 3, 7);
    board[7][4] = std::make_shared<king> (false, 4, 7);
    board[7][5] = std::make_shared<bishop> (false, 5, 7);
    board[7][6] = std::make_shared<knight> (false, 6, 7);
    board[7][7] = std::make_shared<rook> (false, 7, 7);

    // Initialize pawns
    for (int i = 0; i < 8; ++i) {
        board[1][i] = std::make_shared<pawn> (false, i, 1); // Black pawns
        board[6][i] = std::make_shared<pawn> (true, i, 6);  // White pawns
    }
}


bool game::tryMove(int s_col, int s_row, int e_col, int e_row) {
    // Step 1: Check if the source and destination are within bounds (0 to 7)
    if (s_col < 0 || s_col >= 8 || s_row < 0 || s_row >= 8 ||
        e_col < 0 || e_col >= 8 || e_row < 0 || e_row >= 8) {
        return false;  // Move is out of bounds
    }

    // Get pointer to the moving piece
    std::shared_ptr<piece> movingPiece = board[s_col][s_row];

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

    // Step 4: Move the piece to the new position
    board[e_col][e_row] = movingPiece;   // Place the piece at the new position
    board[s_col][s_row] = nullptr;       // Clear the old position

    // Chenge the turn (white/black)
    whiteTurn = !whiteTurn;

    return true;  // Successful move
}


std::shared_ptr<piece> game::getPieceAt(int col, int row) const{
    return board[col][row];
}
