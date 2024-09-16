/**
 * @file logik.cpp
 * @brief Implements the game logik.
 */

#include "logik.h"
#include "game.h"
#include "piece.h"
#include <memory>

#include<iostream>

bool Logik::isLegal(Game* chessGame, int s_col, int s_row, int e_col, int e_row, int promotion) const{
    // Check if the source and destination are within bounds (0 to 7)
    if (s_col < 0 || s_col >= 8 || s_row < 0 || s_row >= 8 ||
        e_col < 0 || e_col >= 8 || e_row < 0 || e_row >= 8) {
        return false;  // Move is out of bounds
    }

    if(s_col == e_col && s_row == e_row){
        return false;
    }

    bool isWhiteTurn = chessGame->getWhiteTurn();

    // Get pointer to the moving piece
    std::shared_ptr<Piece> movingPiece = chessGame->getPieceAt(s_col, s_row);

    // Check if there is a piece at the source position
    if (!movingPiece) {
        return false;  // No piece to move
    }

    // Check correct turn
    if(movingPiece->checkIfWhite() != isWhiteTurn){
        return false;
    }

    // Get the possible moves for the piece and check if the destination is valid
    std::vector<std::pair<int, int>> possibleMoves = movingPiece->getPossibleMoves(chessGame);
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

    // Pinning
    // Simulate the move
    // Create a copy of the game for simulating the move
    Game* simulatedGame = chessGame->clone();
    simulatedGame->updateBoard(s_col, s_row, e_col, e_row);

    if(isPawnPromotion(simulatedGame, s_col, s_row, e_row)) {
        switch (promotion) {
        case 0x10:
            simulatedGame->board[e_col][e_row] = std::make_shared<Bishop>(simulatedGame->board[e_col][e_row]->checkIfWhite(), e_col, e_row);
            break;
        case 0x20:
            simulatedGame->board[e_col][e_row] = std::make_shared<Knight>(simulatedGame->board[e_col][e_row]->checkIfWhite(), e_col, e_row);
            break;
        case 0x30:
            simulatedGame->board[e_col][e_row] = std::make_shared<Rook>(simulatedGame->board[e_col][e_row]->checkIfWhite(), e_col, e_row);
            break;
        case 0x40:
            simulatedGame->board[e_col][e_row] = std::make_shared<Queen>(simulatedGame->board[e_col][e_row]->checkIfWhite(), e_col, e_row);
            break;
        default:
            // Default to Queen if promotion piece is not specified
            simulatedGame->board[e_col][e_row] = std::make_shared<Queen>(simulatedGame->board[e_col][e_row]->checkIfWhite(), e_col, e_row);
            break;
        }
    }

    // Check if the king is in check after the move
    std::pair<int, int> simulKingPosition = simulatedGame->findKing(isWhiteTurn);
    bool simulIsCheck = simulatedGame->isSquareAttacked(simulKingPosition.first, simulKingPosition.second, isWhiteTurn);

    // If the king is in check, the move is illegal
    if (simulIsCheck) {
        delete simulatedGame;
        return false;
    }

    delete simulatedGame;
    return true;
}

bool Logik::isCaptureMove(Game* Game, int s_col, int s_row, int e_col, int e_row) const{
    std::shared_ptr<Piece> startPiece = Game->getPieceAt(s_col, s_row);
    std::shared_ptr<Piece> endPiece = Game->getPieceAt(e_col, e_row);

    // Check if there is an opponent's piece at the destination
    if (endPiece != nullptr && startPiece != nullptr) {
        return startPiece->checkIfWhite() != endPiece->checkIfWhite();
    }

    return false;
}


bool Logik::isCheckmate(Game* game) const {
    // Determine whose turn it is (player who just moved)
    bool isWhiteTurn = game->getWhiteTurn();

    // Check if the opponent is in check
    if(!game->getCheck(!isWhiteTurn)){
        qDebug() << "IS NOT CHECKMATE!!!!!";
        return false;
    }

    // Iterate over all pieces of the opponent
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            std::shared_ptr<Piece> piece = game->board[col][row];

            // If there's a piece and it belongs to the opponent
            if (piece && piece->checkIfWhite() == !isWhiteTurn) {
                // Get all possible moves for this piece
                std::vector<std::pair<int, int>> possibleMoves = piece->getPossibleMoves(game);

                for (const auto& move : possibleMoves) {
                    int targetCol = move.first;
                    int targetRow = move.second;

                    // Simulate the move on a cloned game board
                    Game* simulatedGame = game->clone();
                    simulatedGame->updateBoard(col, row, targetCol, targetRow);

                    // Check if the move leaves the king in check
                    std::pair<int, int> simulKingPosition = simulatedGame->findKing(!isWhiteTurn);
                    bool simulIsCheck = simulatedGame->isSquareAttacked(simulKingPosition.first, simulKingPosition.second, !isWhiteTurn);

                    // If the king is not in check after the move, it's not checkmate
                    if (!simulIsCheck) {
                        delete simulatedGame;
                        qDebug() << "IS NOT A CHECKMATE!";
                        return false;
                    }

                    // Clean up the simulated game
                    delete simulatedGame;
                }
            }
        }
    }

    // No legal moves found and opponent is in check > Checkmate!
    qDebug() << "CHECKMATE!!!!";
    return true;
}


bool Logik::isStalemate(Game* game) const {
    // Determine if it's white or black's turn
    bool isWhiteTurn = game->getWhiteTurn();

    // Find the king's position for the player whose turn it is
    std::pair<int, int> kingPosition = game->findKing(isWhiteTurn);
    if (kingPosition.first == -1 || kingPosition.second == -1) {
        // King not found (hopefully not...)
        return false;
    }

    int kingCol = kingPosition.first;
    int kingRow = kingPosition.second;

    // Check if the current player is in check
    if (game->isSquareAttacked(kingCol, kingRow, isWhiteTurn)) {
        return false;  // If the king is in check, it can't be stalemate
    }

    // Check if any legal move exists for the current player
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            std::shared_ptr<Piece> piece = game->getPieceAt(col, row);

            // If this piece belongs to the current player
            if (piece != nullptr && piece->checkIfWhite() == isWhiteTurn) {
                std::vector<std::pair<int, int>> possibleMoves = piece->getPossibleMoves(game);

                for (const auto& move : possibleMoves) {
                    int moveCol = move.first;
                    int moveRow = move.second;

                    if (this->isLegal(game, col, row, moveCol, moveRow)) {
                        return false;  // If a legal move exists, it's not stalemate
                    }
                }
            }
        }
    }

    // If no legal moves exist and the player is not in check, it's stalemate
    return true;
}




bool Logik::isPawnPromotion(Game* Game, int s_col, int s_row, int e_row) const {

    std::shared_ptr<Piece> piece = Game->getPieceAt(s_col, s_row);

    if (piece != nullptr && dynamic_cast<Pawn*>(piece.get()) != nullptr) {
        // Assume white pawns promote on row 7 and black pawns on row 0
        if ((piece->checkIfWhite() && e_row == 7) ||
            (!piece->checkIfWhite() && e_row == 0)) {
            Game->rowPawnPromotion = e_row;
            return true;

        }
    }

    return false;
}




