/**
 * @file logik.cpp
 * @brief Implements the game logik.
 */

#include "logik.h"
#include "game.h"
#include "piece.h"
#include <memory>

#include<iostream>

bool Logik::isLegal(Game* chessGame, int s_col, int s_row, int e_col, int e_row) const{
    // Step 1: Check if the source and destination are within bounds (0 to 7)
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

    // Step 2: Check if there is a piece at the source position
    if (!movingPiece) {
        return false;  // No piece to move
    }

    //check correct turn
    if(movingPiece->checkIfWhite() != isWhiteTurn){
        return false;
    }

    // Step 3: Get the possible moves for the piece and check if the destination is valid
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

    //check if King is in check
    std::pair<int, int> kingPosition = chessGame->findKing(isWhiteTurn);
    std::pair<int, int> b_kingPosition = chessGame->findKing(!isWhiteTurn);

    bool isCheck = chessGame->isSquareAttacked(kingPosition.first, kingPosition.second, isWhiteTurn);
    bool b_isCheck = chessGame->isSquareAttacked(b_kingPosition.first, kingPosition.second, !isWhiteTurn);

    chessGame->setCheck(isCheck, isWhiteTurn);
    chessGame->setCheck(b_isCheck, !isWhiteTurn);


    //Pinning
    // Simulate the move
    //Create a copy of the game for simulating the move
    Game* simulatedGame = chessGame->clone();


    simulatedGame->updateBoard(s_col, s_row, e_col, e_row);

    // Check if the king is in check after the move
    std::pair<int, int> simulKingPosition = simulatedGame->findKing(isWhiteTurn);
    bool simulIsCheck = simulatedGame->isSquareAttacked(simulKingPosition.first, simulKingPosition.second, isWhiteTurn);

    // If the king is in check, the move is illegal
    if (simulIsCheck) {
        return false;
    }

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


bool Logik::isCheckmate(Game* game, int e_col, int e_row) const {
    // Find the king's position for the player currently under check
    bool isWhiteTurn = !game->getWhiteTurn();
    std::pair<int, int> kingPosition = game->findKing(isWhiteTurn);

    if (kingPosition.first == -1 || kingPosition.second == -1) {
        // King not found, this should not happen in a valid game
        return false;
    }

    int kingCol = kingPosition.first;
    int kingRow = kingPosition.second;

    // Step 1: Is the king currently in check?
    if (!game->isSquareAttacked(kingCol, kingRow, isWhiteTurn)) {
        // If the king is not in check, it's not checkmate
        return false;
    }

    // Step 2: Check if the king has any legal moves to escape check
    std::shared_ptr<Piece> king = game->getPieceAt(kingCol, kingRow);
    std::vector<std::pair<int, int>> kingMoves = king->getPossibleMoves(game);

    for (const auto& move : kingMoves) {
        int newCol = move.first;
        int newRow = move.second;

        // Check if the move is within bounds and does not result in a check
        if (this->isLegal(game, kingCol, kingRow, newCol, newRow) &&
            !game->isSquareAttacked(newCol, newRow, isWhiteTurn)) {
            return false;  // The king can escape check
        }
    }

    // Step 3: Check if any other piece can block the check or capture the threatening piece
    // Loop through all the pieces of the current player and see if any of them can make a move
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            std::shared_ptr<Piece> piece = game->getPieceAt(col, row);

            // Check if this piece belongs to the current player
            if (piece != nullptr && piece->checkIfWhite() == isWhiteTurn) {
                std::vector<std::pair<int, int>> possibleMoves = piece->getPossibleMoves(game);

                for (const auto& move : possibleMoves) {
                    int moveCol = move.first;
                    int moveRow = move.second;

                    // Simulate the move and check if it prevents the check
                    if (this->isLegal(game, col, row, moveCol, moveRow)) {
                        // Temporarily make the move on a simulated board
                        Game* tempGame = game->clone();  // Make a copy of the game
                        tempGame->updateBoard(col, row, moveCol, moveRow);

                        // Check if the king is still in check
                        if (!tempGame->isSquareAttacked(kingCol, kingRow, isWhiteTurn)) {
                            return false;  // The check can be avoided
                        }
                    }
                }
            }
        }
    }

    // Step 4: If no legal moves can prevent the check, it's checkmate
    return true;
}


bool Logik::isStalemate(Game* game) const {
    // Determine if it's white or black's turn
    bool isWhiteTurn = game->getWhiteTurn();  // True for white, false for black

    // Find the king's position for the player whose turn it is
    std::pair<int, int> kingPosition = game->findKing(isWhiteTurn);
    if (kingPosition.first == -1 || kingPosition.second == -1) {
        // King not found, this should not happen in a valid game
        return false;
    }

    int kingCol = kingPosition.first;
    int kingRow = kingPosition.second;

    // Step 1: Check if the current player is in check
    if (game->isSquareAttacked(kingCol, kingRow, isWhiteTurn)) {
        return false;  // If the king is in check, it can't be stalemate
    }

    // Step 2: Check if any legal move exists for the current player
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

    // Step 3: If no legal moves exist and the player is not in check, it's stalemate
    return true;
}


bool Logik::isCastlingMove(Game* Game, int s_col, int s_row, int e_col, int e_row) const{  
    std::shared_ptr<Piece> king = Game->getPieceAt(s_col, s_row);
    std::shared_ptr<Piece> rook = Game->getPieceAt(e_col, e_row);

    if (king == nullptr || dynamic_cast<King*>(king.get()) == nullptr) {
        return false;
    }
    if (rook == nullptr || dynamic_cast<Rook*>(rook.get()) == nullptr) {
        return false;
    }

    // Check castling rules
    if (king->checkMoved() || rook->checkMoved()) {
        return false;
    }

    int min_col = std::min(s_col, e_col);
    int max_col = std::max(s_col, e_col);
    for (int col = min_col + 1; col < max_col; ++col) {
        if (Game->getPieceAt(col, s_row) != nullptr) {
            return false;
        }
    }

    // Check if the squares the king will move through are not attacked
    for (int col = std::min(s_col, e_col); col <= std::max(s_col, e_col); ++col) {
        if (Game->isSquareAttacked(col, s_row, king->checkIfWhite())) {
            return false;
        }
    }

    return true;
}



bool Logik::isPawnPromotion(Game* Game, int s_col, int s_row, int e_col, int e_row) const {

    std::shared_ptr<Piece> piece = Game->getPieceAt(s_col, s_row);

    if (piece != nullptr && dynamic_cast<Pawn*>(piece.get()) != nullptr) {
        // Assume white pawns promote on row 7 and black pawns on row 0
        if ((piece->checkIfWhite() && e_row == 7) ||
            (!piece->checkIfWhite() && e_row == 0)) {
            return true;
        }
    }

    return false;
}




