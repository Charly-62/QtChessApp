/**
 * @file game.cpp
 * @brief This file contains the implementation of the game class which manages the chessboard and some game logic.
 */

#include "game.h"
#include "logik.h"
#include "piece.h"

Game::Game(class SchachApp* gui, class Netzwerk* netzwerkInstance)
    : whiteTurn(true), gui(gui), netzwerkInstance(netzwerkInstance) {
    initBoard();
}


Game::~Game() {}


void Game::initBoard() {
    // Initialize white pieces
    board[0][0] = std::make_shared<Rook> (true, 0, 0);
    board[1][0] = std::make_shared<Knight> (true, 1, 0);
    board[2][0] = std::make_shared<Bishop> (true, 2, 0);
    board[3][0] = std::make_shared<Queen> (true, 3, 0);
    board[4][0] = std::make_shared<King> (true, 4, 0);
    board[5][0] = std::make_shared<Bishop> (true, 5, 0);
    board[6][0] = std::make_shared<Knight> (true, 6, 0);
    board[7][0] = std::make_shared<Rook> (true, 7, 0);

    // Initialize black pieces
    board[0][7] = std::make_shared<Rook> (false, 0, 7);
    board[1][7] = std::make_shared<Knight> (false, 1, 7);
    board[2][7] = std::make_shared<Bishop> (false, 2, 7);
    board[3][7] = std::make_shared<Queen> (false, 3, 7);
    board[4][7] = std::make_shared<King> (false, 4, 7);
    board[5][7] = std::make_shared<Bishop> (false, 5, 7);
    board[6][7] = std::make_shared<Knight> (false, 6, 7);
    board[7][7] = std::make_shared<Rook> (false, 7, 7);

    // Initialize pawns
    for (int i = 0; i < 8; ++i) {
        board[i][1] = std::make_shared<Pawn> (true, i, 1); // White pawns
        board[i][6] = std::make_shared<Pawn> (false, i, 6);  // Black pawns
    }
}


MoveInfo Game::tryMove(int s_col, int s_row, int e_col, int e_row) {
    MoveInfo moveInfo = {s_col, s_row, e_col, e_row, 0x00, 0x00,true};

    // Check legality of the move
    if (!logikInstance.isLegal(this, s_col, s_row, e_col, e_row)) {
        moveInfo.islegal=false;
        return moveInfo; // Will handle the error in the future
    }

    // Determine consequences (capture, checkmate, etc.)
    if (logikInstance.isCaptureMove(this, s_col, s_row, e_col, e_row)) {
        moveInfo.consequences = 0x01;  // schlägt
    }
    if (logikInstance.isCheckmate(this, e_col, e_row)) {
        moveInfo.consequences = (moveInfo.consequences == 0x01) ? 0x03 : 0x02;  // checkmate or capture and checkmate
    }
    if (logikInstance.isCastlingMove(this, s_col, s_row, e_col, e_row)) {
        moveInfo.consequences = 0x04;  // Rochade
    }

    // Check for pawn promotion
    if (logikInstance.isPawnPromotion(this, s_col, s_row, e_col, e_row)) {
        moveInfo.promotion = getPawnPromotion();
    }

    // Apply the move to the board (update the game state)
    updateBoard(s_col, s_row, e_col, e_row);

    std::shared_ptr<Piece> movingPiece = getPieceAt(e_col, e_row);

    //change the Piece hasMoved boolean to true
    movingPiece->setMoved();

    // Chenge the turn (white/black)
    whiteTurn = !whiteTurn;

    return moveInfo;  // Return moveInfo struct
}


std::shared_ptr<Piece> Game::getPieceAt(int col, int row) const{
    return board[col][row];
}

bool Game::isSquareAttacked(int col, int row, bool currentPlayerIsWhite) const {
    // Loop over all squares on the board
    for (int c = 0; c < 8; ++c) {
        for (int r = 0; r < 8; ++r) {
            std::shared_ptr<Piece> piece = getPieceAt(c, r);

            // Check if there is a piece at (c, r) and it's from the opponent's team
            if (piece != nullptr && piece->checkIfWhite() != currentPlayerIsWhite) {
                // Check if the opponent's piece can move to (col, row)
                std::vector<std::pair<int, int>> possibleMoves = piece->getPossibleMoves();
                for (const auto& move : possibleMoves) {
                    if (move.first == col && move.second == row) {
                        return true; // The square is under attack
                    }
                }
            }
        }
    }

    return false; // The square is not under attack
}


void Game::updateBoard(int s_col, int s_row, int e_col, int e_row) {
    std::shared_ptr<Piece> movingPiece = getPieceAt(s_col, s_row);
    board[e_col][e_row] = movingPiece;   // Place the piece at the new position
    board[s_col][s_row] = nullptr;       // Clear the old position
    movingPiece->setPosition(e_row, e_col); //change Piece internal Position
}

quint8 Game::getPawnPromotion() {
    return true;
}

std::pair<int, int> Game::findKing(bool isWhite) const {
    // Loop through the entire board (assuming 8x8 board)
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            std::shared_ptr<Piece> piece = getPieceAt(col, row);

            // Check if the piece is a King and belongs to the specified team
            if (piece != nullptr && dynamic_cast<King*>(piece.get()) != nullptr && piece->checkIfWhite() == isWhite) {
                // Return the position of the King (col, row)
                return {col, row};
            }
        }
    }

    // If no king is found (should never happen in a valid game), return an invalid position (-1, -1)
    return {-1, -1};
}
