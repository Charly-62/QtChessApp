/**
 * @file main.cpp
 * @brief This file contains the main function for the chess programm.
 */

#include <iostream>

#include "schachapp.h"
#include "game.h"
#include "netzwerk.h"

#include <QApplication>

using namespace std;


void printBoard(const Game& game) {
    for (int row = 7; row >= 0; --row) {
        for (int col = 0; col < 8; ++col) {
            std::shared_ptr<Piece> piece = game.getPieceAt(col, row);
            if (piece) {
                char pieceChar = ' ';
                if (dynamic_cast<Pawn*>(piece.get())) pieceChar = 'P';
                else if (dynamic_cast<Rook*>(piece.get())) pieceChar = 'R';
                else if (dynamic_cast<Knight*>(piece.get())) pieceChar = 'N';
                else if (dynamic_cast<Bishop*>(piece.get())) pieceChar = 'B';
                else if (dynamic_cast<Queen*>(piece.get())) pieceChar = 'Q';
                else if (dynamic_cast<King*>(piece.get())) pieceChar = 'K';
                std::cout << pieceChar << ' ';
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /// Create the GUI instance
    SchachApp gui;

    /// Create the Netzwerk instance (pass the Game instance once it's created)
    Netzwerk netzwerk(nullptr);

    /// Create the Game instance and pass it to netzwerk
    Game Game(&gui, &netzwerk);
    netzwerk.setGame(&Game);

    printBoard(Game);
    Game.tryMove(4, 1, 4, 2);

    printBoard(Game);

    cout << "King Location:" << Game.findKing(1).first << " " << Game.findKing(1).second;

    /// Show the GUI
    gui.show();

    /// Start the Qt event loop
    return a.exec();
}
