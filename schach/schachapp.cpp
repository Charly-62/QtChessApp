#include "schachapp.h"
#include "ui_schachgui.h"
#include "piece.h"
#include <QPushButton>


SchachApp::SchachApp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SchachApp)
    , selectedRow(-1)
    , selectedCol(-1)
    ,chessGame(new Game(this,nullptr))
{
    ui->setupUi(this);
    initializeBoard();
    setupChessBoard();
}

SchachApp::~SchachApp()
{
    delete ui;
    for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                delete board[row][col];
            }
     }
}

void SchachApp::initializeBoard()
{
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            buttons[row][col] = nullptr;
            board[row][col] = nullptr;
        }
    }

    // Map UI buttons to the grid
    buttons[0][0] = ui->A1; buttons[0][1] = ui->B1; buttons[0][2] = ui->C1; buttons[0][3] = ui->D1;
    buttons[0][4] = ui->E1; buttons[0][5] = ui->F1; buttons[0][6] = ui->G1; buttons[0][7] = ui->H1;
    buttons[1][0] = ui->A2; buttons[1][1] = ui->B2; buttons[1][2] = ui->C2; buttons[1][3] = ui->D2;
    buttons[1][4] = ui->E2; buttons[1][5] = ui->F2; buttons[1][6] = ui->G2; buttons[1][7] = ui->H2;
    buttons[2][0] = ui->A3; buttons[2][1] = ui->B3; buttons[2][2] = ui->C3; buttons[2][3] = ui->D3;
    buttons[2][4] = ui->E3; buttons[2][5] = ui->F3; buttons[2][6] = ui->G3; buttons[2][7] = ui->H3;
    buttons[3][0] = ui->A4; buttons[3][1] = ui->B4; buttons[3][2] = ui->C4; buttons[3][3] = ui->D4;
    buttons[3][4] = ui->E4; buttons[3][5] = ui->F4; buttons[3][6] = ui->G4; buttons[3][7] = ui->H4;
    buttons[4][0] = ui->A5; buttons[4][1] = ui->B5; buttons[4][2] = ui->C5; buttons[4][3] = ui->D5;
    buttons[4][4] = ui->E5; buttons[4][5] = ui->F5; buttons[4][6] = ui->G5; buttons[4][7] = ui->H5;
    buttons[5][0] = ui->A6; buttons[5][1] = ui->B6; buttons[5][2] = ui->C6; buttons[5][3] = ui->D6;
    buttons[5][4] = ui->E6; buttons[5][5] = ui->F6; buttons[5][6] = ui->G6; buttons[5][7] = ui->H6;
    buttons[6][0] = ui->A7; buttons[6][1] = ui->B7; buttons[6][2] = ui->C7; buttons[6][3] = ui->D7;
    buttons[6][4] = ui->E7; buttons[6][5] = ui->F7; buttons[6][6] = ui->G7; buttons[6][7] = ui->H7;
    buttons[7][0] = ui->A8; buttons[7][1] = ui->B8; buttons[7][2] = ui->C8; buttons[7][3] = ui->D8;
    buttons[7][4] = ui->E8; buttons[7][5] = ui->F8; buttons[7][6] = ui->G8; buttons[7][7] = ui->H8;
}



void SchachApp::setupChessBoard() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            // Add pieces to the initial board setup
            if (row == 0) { // White back row
                setupPieces(row, col, buttons[row][col], true);
            } else if (row == 1) { // White pawns
                buttons[row][col]->setIcon(QIcon(":/Figuren/pawnW.png"));
            } else if (row == 6) { // Black pawns
                buttons[row][col]->setIcon(QIcon(":/Figuren/pawnB.png"));
            } else if (row == 7) { // Black back row
                setupPieces(row, col, buttons[row][col], false);
            }

            // Set the icon size and connect the button click to the handler
            buttons[row][col]->setIconSize(QSize(80, 80));
            connect(buttons[row][col], &QPushButton::clicked, [=]() {
            handleSquareClick(row, col);
            });
        }
    }
}

void SchachApp::setupPieces(int row, int col, QPushButton* button, bool isWhite) {
    QString prefix = isWhite ? "W" : "B";
    QString pieceType;

    if (col == 0 || col == 7)
        pieceType = "rook";
    else if (col == 1 || col == 6)
        pieceType = "horse";
    else if (col == 2 || col == 5)
        pieceType = "bishop";
    else if (col == 3)
        pieceType = "queen";
    else if (col == 4)
        pieceType = "king";

    button->setIcon(QIcon(":/Figuren/" + pieceType + prefix + ".png"));
    button->setIconSize(QSize(80, 80));

}

void SchachApp::handleSquareClick(int row, int col) {
    QPushButton* clickedButton = buttons[row][col];

    if (selectedRow == -1 && selectedCol == -1) { // No piece selected yet
        if (!clickedButton->icon().isNull()) { // If there's a piece on the square
            selectedRow = row;
            selectedCol = col;
          //  clickedButton->setStyleSheet("background-color: yellow;"); // Highlight selected square
        }
    } else { // A piece is selected and a move is attempted
     //   MoveInfo moveInfo = chessGame->tryMove(selectedCol, selectedRow, col, row);

         // Assuming `tryMove` returns valid MoveInfo with valid information indicating success
     //    if (moveInfo.consequences != 0) { // Adjust this condition based on how you determine a successful move
            movePiece(selectedRow, selectedCol, row, col);
     //    } else {
          // Optionally show an error message or visual feedback for invalid move
      //    }

               // Reset selected piece state
         resetButtonStyle(selectedRow, selectedCol);
         resetButtonStyle(row, col);
         selectedRow = -1;
         selectedCol = -1;
           }
}

void SchachApp::movePiece(int fromRow, int fromCol, int toRow, int toCol) {
    QPushButton* fromButton = buttons[fromRow][fromCol];
    QPushButton* toButton = buttons[toRow][toCol];

    // Move the icon from the selected button to the target button
    toButton->setIcon(fromButton->icon());
    fromButton->setIcon(QIcon());  // Clear the icon from the original button

    resetButtonStyle(fromRow, fromCol);  // Reset the original button style
    resetButtonStyle(toRow, toCol);  // Reset the target button style
}

void SchachApp::resetButtonStyle(int row, int col) {
    // Reset the button's background color based on its position
    bool isWhiteSquare = (row + col) % 2 == 0;
    buttons[row][col]->setStyleSheet(isWhiteSquare ? "background-color: white;" : "background-color: black;");
}
