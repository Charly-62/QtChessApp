/**
 * @file game.cpp
 * @brief This file contains the implementation of the game class which manages the chessboard and some game logic.
 */

#include "game.h"
#include "logik.h"
#include "piece.h"
#include "schachapp.h"
#include <iostream>
#include <QString>
#include <QComboBox>

Game::Game(class SchachApp* gui, QObject* parent)
    : QObject(parent), whiteTurn(true), gui(gui){
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
        moveInfo.islegal = false;
        return moveInfo;
    }

    // Determine consequences (capture, checkmate, etc.)
    moveInfo.consequences = 0x00; // schlägt nicht by default

    if (logikInstance.isCaptureMove(this, s_col, s_row, e_col, e_row)) {
        moveInfo.consequences = 0x01;  // schlägt
    }
    if (logikInstance.isCheckmate(this, e_col, e_row)) {
        std::cout << "checkmate!!!!";
        moveInfo.consequences = (moveInfo.consequences == 0x01) ? 0x03 : 0x02;  // checkmate or capture and checkmate
    }
    if (logikInstance.isCastlingMove(this, s_col, s_row, e_col, e_row)) {
        moveInfo.consequences = 0x04;  // Rochade
    }

    // Check for pawn promotion
    moveInfo.promotion = 0x00; // no promotion by default

    if (logikInstance.isPawnPromotion(this, s_col, s_row, e_col, e_row)) {
        moveInfo.promotion = getPawnPromotion();
    }

    // Apply the move to the board (update the game state)
    updateBoard(s_col, s_row, e_col, e_row);

    return moveInfo;  // Return moveInfo struct
}

std::shared_ptr<Piece> Game::getPieceAt(int col, int row) const{
    return board[col][row];
}

bool Game::isSquareAttacked(int col, int row, bool currentPlayerIsWhite) const {
    // Loop over all squares on the board
    for (int c = 0; c < 8; ++c) {
        for (int r = 0; r < 8; ++r) {

            std::shared_ptr<Piece> attackingPiece = getPieceAt(c, r);

            // Check if there is a piece at (c, r) and it's from the opponent's team
            if (attackingPiece != nullptr && attackingPiece->checkIfWhite() != currentPlayerIsWhite) {
                // Check if the opponent's piece can move to (col, row)
                std::vector<std::pair<int, int>> possibleMoves = attackingPiece->getPossibleMoves(this);
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


    // Check if the move is an en passant capture
    if (movingPiece->getType() == "pawn" && s_col != e_col && getPieceAt(e_col, e_row) == nullptr) {
        // This means the pawn moved diagonally to an empty square, indicating en passant
        int capturedPawnRow = (movingPiece->checkIfWhite()) ? e_row - 1 : e_row + 1;
        std::shared_ptr<Piece> capturedPawn = getPieceAt(e_col, capturedPawnRow);

        // Ensure the captured piece is an opponent's pawn (this should always be true, but we check for safety)
        if (capturedPawn != nullptr && capturedPawn->getType() == "pawn" && capturedPawn->checkIfWhite() != movingPiece->checkIfWhite() && e_col == this->lastMoveWasTwoSquarePawnMove) {
            // Remove the captured pawn from the board
            board[e_col][capturedPawnRow] = nullptr;
        }
    }

    board[e_col][e_row] = movingPiece;   // Place the piece at the new position
    board[s_col][s_row] = nullptr;       // Clear the old position
    movingPiece->setPosition(e_row, e_col); // change Piece internal Position

    if (movingPiece->getType() == "pawn") {  // Check if the moving piece is a pawn
        int rowDifference = abs(e_row - s_row);
        // Check if the move was exactly two squares vertically
        if (rowDifference == 2) {
            this->lastMoveWasTwoSquarePawnMove = e_col;
        }
    }else{
        this->lastMoveWasTwoSquarePawnMove =  8;
    }

    //change the Piece hasMoved boolean to true
    movingPiece->setMoved();
    // Change the turn
    switchTurn();
}

quint8 Game::getPawnPromotion() {

    //return 0x30;
    return gui->PawnPromotion();

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

void Game::switchTurn() {
    whiteTurn = !whiteTurn;
    emit turnSwitched(whiteTurn);
}

Game* Game::clone() const {
    Game* clonedGame = new Game(gui);

    // Copy the relevant game state
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; j++){
            if (board[i][j] != nullptr) {
                clonedGame->board[i][j] = board[i][j]->clone();
            }else{
                clonedGame->board[i][j] = nullptr;
            }
        }
    }

    return clonedGame;
}
