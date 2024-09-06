#include "schachapp.h"
#include "ui_schachgui.h"
#include "piece.h"
#include "game.h"
#include <QPushButton>

#include <QDebug>
#include <iostream>


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


// Setup chessboard in GUI
void SchachApp::setupChessBoard() {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            std::shared_ptr<Piece> piece = chessGame->getPieceAt(col, row);  // Get piece from the game
            if (piece != nullptr) {  // If there is a piece at this position
                QString iconName = QString(":/Figuren/") + piece->getType() + (piece->checkIfWhite() ? "W" : "B") + ".png";
                buttons[row][col]->setIcon(QIcon(iconName));
            }
            // Set the icon size and connect the button click to the handler
            buttons[row][col]->setIconSize(QSize(80, 80));

            if (!originalButtonStyles.contains(buttons[row][col])) {
                            originalButtonStyles[buttons[row][col]] = buttons[row][col]->styleSheet();
                        }
            connect(buttons[row][col], &QPushButton::clicked, [=]() {
                handleSquareClick(row, col);
            });
        }
    }
}
void SchachApp::highlightPossibleMoves(const std::vector<std::pair<int, int>>& moves) {
    // Store the original styles of the buttons to be highlighted
    for (const auto& move : moves) {
        int row = move.second;
        int col = move.first;
        QPushButton* button = buttons[row][col];
        if (button) {
            if (!originalButtonStyles.contains(button)) {
                originalButtonStyles[button] = button->styleSheet(); // Store the current style if not already stored
            }
            button->setStyleSheet("background-color: red;");
        }
    }
}

void SchachApp::resetBoardHighlight() {
    // Reset only the highlighted buttons to their original style
    for (auto it = originalButtonStyles.begin(); it != originalButtonStyles.end(); ++it) {
        QPushButton* button = it.key();
        if (button) {
            button->setStyleSheet(it.value()); // Reset to original style
        }
    }
}



void SchachApp::handleSquareClick(int row, int col) {
    QPushButton* clickedButton = buttons[row][col];
    std::shared_ptr<Piece> selectedPiece = chessGame->getPieceAt(col, row);

    if(selectedPiece){
        std::vector<std::pair<int, int>> possibleMoves = selectedPiece->getPossibleMoves();
        highlightPossibleMoves(possibleMoves);
        for (const auto& move : possibleMoves) {
            std::cout << move.first << " " << move.second << std::endl;
        }
    }

    if (selectedRow == -1 && selectedCol == -1) { // No piece selected yet
        if (!clickedButton->icon().isNull()) { // If there's a piece on the square
            selectedRow = row;
            selectedCol = col;
            qDebug() << "Selected piece at:" << selectedRow << selectedCol;
          //  clickedButton->setStyleSheet("background-color: yellow;"); // Highlight selected square

        }
    } else { // A piece is selected and a move is attempted
        qDebug() << "Attempting to move to:" << row << col;
       // Attempt to move and get MoveInfo
                MoveInfo moveInfo = chessGame->tryMove(selectedCol, selectedRow, col, row);
                qDebug() << "isLegal:" << moveInfo.islegal;

                if (moveInfo.islegal != 0) { // Move is valid
                    movePiece(selectedRow, selectedCol, row, col);
                    resetBoardHighlight();

                    for (int row = 7; row >= 0; --row) {
                        for (int col = 0; col < 8; ++col) {
                            std::shared_ptr<Piece> piece = chessGame->getPieceAt(col, row);
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

                // Reset selection
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

     // Debugging: Print the move details
     qDebug() << "Moved piece from:" << fromRow << fromCol << "to:" << toRow << toCol;

     // Re-fetch the piece and update the icon (ensures any changes are reflected)
     std::shared_ptr<Piece> movedPiece = chessGame->getPieceAt(toCol, toRow);
     if (movedPiece != nullptr) {
        QString iconName = QString(":/Figuren/") + movedPiece->getType() + (movedPiece->checkIfWhite() ? "W" : "B") + ".png";
        toButton->setIcon(QIcon(iconName));  // Set the correct icon for the piece
      } else {
         toButton->setIcon(QIcon());  // Clear icon if no piece exists (for safety)
      }

}


/**
 * @brief Changes the color of the IPAddress line edit if it is a valid or invalid IPv4 address (maybe add also IPv6 addresses)
 * @param arg1
 */
void SchachApp::on_leIP_textChanged(const QString &arg1)
{
    QString state = "0";

    if(arg1 == "...") {
        state = "";
    } else {
        QHostAddress address(arg1);
        if(QAbstractSocket::IPv4Protocol == address.protocol()) {
            state = "1";
        }
    }

    ui->leIP->setProperty("state", state);
    style()->polish(ui->leIP);
}

void SchachApp::on_bConnect_clicked()
{
    auto ip = ui->leIP->text();
    auto port = ui->spnPort->value();
    // _client.connectToHost(ip, port);
}
