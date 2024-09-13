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
#include <QEvent>

Game::Game(class SchachApp* gui, QObject* parent)
    : QObject(parent), whiteTurn(true), gui(gui)
{
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
    MoveInfo moveInfo = {s_col, s_row, e_col, e_row,
                         0x00, 0x00, true,
                         nullptr, false, false, 8, nullptr,
                         -1, -1, nullptr};

    // Check legality of the move
    if (!logikInstance.isLegal(this, s_col, s_row, e_col, e_row)) {
        moveInfo.islegal = false;
        return moveInfo;
    }

    std::shared_ptr<Piece> movingPiece = getPieceAt(s_col, s_row);

    // Store the captured piece
    moveInfo.capturedPiece = getPieceAt(e_col, e_row);

    // Store hasMoved flags
    moveInfo.movedPieceHasMovedBefore = movingPiece->checkMoved();

    // For en passant, store the captured pawn
    if (movingPiece->getType() == "pawn" && s_col != e_col && getPieceAt(e_col, e_row) == nullptr) {
        int capturedPawnRow = (movingPiece->checkIfWhite()) ? e_row - 1 : e_row + 1;
        moveInfo.enPassantCapturedPawn = getPieceAt(e_col, capturedPawnRow);
    }

    // Store lastMoveWasTwoSquarePawnMove
    moveInfo.lastMoveWasTwoSquarePawnMoveBefore = lastMoveWasTwoSquarePawnMove;

    // For castling, store rook info
    if (movingPiece->getType() == "king" && abs(e_col - s_col) == 2) {
        // Determine rook positions
        if (e_col == 6) {  // Kingside castling
            moveInfo.rookStartCol = 7;
            moveInfo.rookEndCol = 5;
            std::shared_ptr<Piece> rook = getPieceAt(7, s_row);
            moveInfo.rookHasMovedBefore = rook->checkMoved();
        } else if (e_col == 2) {  // Queenside castling
            moveInfo.rookStartCol = 0;
            moveInfo.rookEndCol = 3;
            std::shared_ptr<Piece> rook = getPieceAt(0, s_row);
            moveInfo.rookHasMovedBefore = rook->checkMoved();
        }
    }

    // For pawn promotion, store the pawn before promotion
    if (logikInstance.isPawnPromotion(this, s_col, s_row, e_row)) {
        moveInfo.pawnBeforePromotion = movingPiece; // Store the pawn
    }

    // Determine consequences (capture, checkmate, etc.)
    moveInfo.consequences = 0x00; // By default, no capture

    if (logikInstance.isCaptureMove(this, s_col, s_row, e_col, e_row)) {
        moveInfo.consequences = 0x01;  // Capture
    }


    // Check for pawn promotion
    moveInfo.promotion = 0x00; // No promotion by default

    if (logikInstance.isPawnPromotion(this, s_col, s_row, e_row)) {
        qWarning() <<"game choose promotion!";
        moveInfo.promotion = gui->PawnPromotion(rowPawnPromotion);
        qWarning() << "game promotion!" << moveInfo.promotion;

        switch(moveInfo.promotion){
            case 16:
                board[s_col][s_row] = std::make_shared<Bishop> (true, s_col, s_row);
            break;
            case 32:
                board[s_col][s_row] = std::make_shared<Knight> (true, s_col, s_row);
            break;
            case 48:
                board[s_col][s_row] = std::make_shared<Rook> (true, s_col, s_row);
            break;
            case 64:
                board[s_col][s_row] = std::make_shared<Queen> (true, s_col, s_row);
            break;
        }


        }
        // Apply the move to the board (update the game state)
        updateBoard(s_col, s_row, e_col, e_row);

        if (logikInstance.isCheckmate(this)) {
            std::cout << "Checkmate!";
            isCheckmate = true;
            moveInfo.consequences = (moveInfo.consequences == 0x01) ? 0x03 : 0x02;  // Checkmate or capture and checkmate
        }

        return moveInfo;  // Return moveInfo struct
}

std::shared_ptr<Piece> Game::getPieceAt(int col, int row) const{
    return board[col][row];
}

bool Game::isSquareAttacked(int col, int row, bool currentPlayerIsWhite) const {
    // Loop over all squares on the board
    for (int c = 0; c < 8; ++c) {
        for (int r = 0; r < 8; ++r) {
            if (c != col || r != row){
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
    }

    return false; // The square is not under attack
}


void Game::updateBoard(int s_col, int s_row, int e_col, int e_row) {
    qDebug() << "updateBoard";
    std::shared_ptr<Piece> movingPiece = getPieceAt(s_col, s_row);

    // --- CASTLING LOGIC ---
    if (movingPiece->getType() == "king") {
        // Castling occurs if the king moves two squares left (queenside) or right (kingside)
        if (abs(e_col - s_col) == 2) {
            // Determine if it's kingside or queenside castling
            if (e_col == 6) {  // Kingside castling (king moves to column 6)
                // Move the rook from column 7 to column 5
                std::shared_ptr<Piece> rook = getPieceAt(7, s_row);
                board[5][s_row] = rook;
                board[7][s_row] = nullptr;
                rook->setPosition(s_row, 5);
                rook->setMoved(true);  // Mark the rook as having moved
            }
            else if (e_col == 2) {  // Queenside castling (king moves to column 2)
                // Move the rook from column 0 to column 3
                std::shared_ptr<Piece> rook = getPieceAt(0, s_row);
                board[3][s_row] = rook;
                board[0][s_row] = nullptr;
                rook->setPosition(s_row, 3);
                rook->setMoved(true);  // Mark the rook as having moved
            }
        }
    }


    // --- EN PASSANT LOGIC ---
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
    movingPiece->setMoved(true);
    // Change the turn
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
    qDebug() << "isWhiteTurn switched in Game";
    whiteTurn = !whiteTurn;
}

void Game::switchTurn(bool turn) {
    whiteTurn = turn;
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

void Game::undoMove(MoveInfo moveInfo) {

    // Get the moving piece
    std::shared_ptr<Piece> movingPiece = getPieceAt(moveInfo.e_col, moveInfo.e_row);

    // Move the piece back to its original position
    board[moveInfo.s_col][moveInfo.s_row] = movingPiece;
    movingPiece->setPosition(moveInfo.s_row, moveInfo.s_col);

    // Restore the hasMoved flag
    movingPiece->setMoved(moveInfo.movedPieceHasMovedBefore);

    // Clear the end position
    board[moveInfo.e_col][moveInfo.e_row] = nullptr;

    // If there was a captured piece, restore it
    if (moveInfo.capturedPiece) {
        board[moveInfo.e_col][moveInfo.e_row] = moveInfo.capturedPiece;
        moveInfo.capturedPiece->setPosition(moveInfo.e_row, moveInfo.e_col);
    }

    // Handle special moves
    // Castling
    if (movingPiece->getType() == "king" && abs(moveInfo.e_col - moveInfo.s_col) == 2) {
        // Move the rook back to its original position
        std::shared_ptr<Piece> rook = getPieceAt(moveInfo.rookEndCol, moveInfo.e_row);
        board[moveInfo.rookStartCol][moveInfo.e_row] = rook;
        rook->setPosition(moveInfo.e_row, moveInfo.rookStartCol);
        rook->setMoved(moveInfo.rookHasMovedBefore);

        // Clear the rook's end position
        board[moveInfo.rookEndCol][moveInfo.e_row] = nullptr;
    }

    // En passant
    if (moveInfo.enPassantCapturedPawn) {
        int capturedPawnRow = (movingPiece->checkIfWhite()) ? moveInfo.e_row - 1 : moveInfo.e_row + 1;
        board[moveInfo.e_col][capturedPawnRow] = moveInfo.enPassantCapturedPawn;
        moveInfo.enPassantCapturedPawn->setPosition(capturedPawnRow, moveInfo.e_col);
    }

    // Promotion
    if (moveInfo.promotion != 0x00) {
        // Replace the promoted piece with the original pawn
        board[moveInfo.s_col][moveInfo.s_row] = moveInfo.pawnBeforePromotion;
        movingPiece = nullptr;
    }

    // Restore lastMoveWasTwoSquarePawnMove
    lastMoveWasTwoSquarePawnMove = moveInfo.lastMoveWasTwoSquarePawnMoveBefore;

    // Switch the turn back
    whiteTurn = !whiteTurn;
}
