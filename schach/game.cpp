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
    board[0][1] = std::make_shared<Knight> (true, 1, 0);
    board[0][2] = std::make_shared<Bishop> (true, 2, 0);
    board[0][3] = std::make_shared<Queen> (true, 3, 0);
    board[0][4] = std::make_shared<King> (true, 4, 0);
    board[0][5] = std::make_shared<Bishop> (true, 5, 0);
    board[0][6] = std::make_shared<Knight> (true, 6, 0);
    board[0][7] = std::make_shared<Rook> (true, 7, 0);

    // Initialize black pieces
    board[7][0] = std::make_shared<Rook> (false, 0, 7);
    board[7][1] = std::make_shared<Knight> (false, 1, 7);
    board[7][2] = std::make_shared<Bishop> (false, 2, 7);
    board[7][3] = std::make_shared<Queen> (false, 3, 7);
    board[7][4] = std::make_shared<King> (false, 4, 7);
    board[7][5] = std::make_shared<Bishop> (false, 5, 7);
    board[7][6] = std::make_shared<Knight> (false, 6, 7);
    board[7][7] = std::make_shared<Rook> (false, 7, 7);

    // Initialize pawns
    for (int i = 0; i < 8; ++i) {
        board[1][i] = std::make_shared<Pawn> (false, i, 1); // Black pawns
        board[6][i] = std::make_shared<Pawn> (true, i, 6);  // White pawns
    }
}


MoveInfo Game::tryMove(int s_col, int s_row, int e_col, int e_row) {
    MoveInfo moveInfo = {s_col, s_row, e_col, e_row, 0x00, 0x00};

    // Check legality of the move
    if (!logikInstance.isLegal(this, s_col, s_row, e_col, e_row)) {
        return moveInfo;  // Will handle the error in the future
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
    if (logikInstance.isPawnPromotion(this, e_col, e_row)) {
        moveInfo.promotion = getPawnPromotion();
    }

    // Apply the move to the board (update the game state)
    updateBoard(s_col, s_row, e_col, e_row);

    std::shared_ptr<Piece> movingPiece = getPieceAt(s_col, s_row);

    // Chenge the turn (white/black)
    whiteTurn = !whiteTurn;

    return moveInfo;  // Return moveInfo struct
}


std::shared_ptr<Piece> Game::getPieceAt(int col, int row) const{
    return board[col][row];
}


void Game::updateBoard(int s_col, int s_row, int e_col, int e_row) {
    std::shared_ptr<Piece> movingPiece = getPieceAt(s_col, s_row);
    board[e_col][e_row] = movingPiece;   // Place the piece at the new position
    board[s_col][s_row] = nullptr;       // Clear the old position
}

quint8 Game::getPawnPromotion() {

}
