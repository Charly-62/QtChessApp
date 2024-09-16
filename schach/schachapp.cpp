#include "schachapp.h"
#include "ui_schachgui.h"
#include "mytcpclient.h"
#include "piece.h"
#include "game.h"



SchachApp::SchachApp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SchachApp)
    , selectedRow(-1)
    , selectedCol(-1)
    , previouslySelectedCol(-1)
    , previouslySelectedRow(-1)
    , chessGame(new Game(this))
    , client(nullptr)
    , server(nullptr)
{
    ui->setupUi(this);
    ui-> GAME ->setCurrentWidget(ui->initalpage);
    // initializeBoard();
    // setupChessBoard();
    setDeviceController();

    on_cbHostClient_currentTextChanged("Local");
    isLocalPlayerWhite = false;

    ui->pbUndo->setEnabled(false);
    ui->pbUndoAccept->setEnabled(false);
    ui->pbUndoDeny->setEnabled(false);

    player1Timer = new QTimer(this);
    player2Timer = new QTimer(this);
    player1TimeRemaining = 10 * 60;  // Set the initial time to 10 minutes (in seconds)
    player2TimeRemaining = 10 * 60;  // Set the initial time to 10 minutes (in seconds)

    // Connect the QTimer signals to the corresponding slot functions
    connect(player1Timer, &QTimer::timeout, this, &SchachApp::updatePlayer1Timer);
    connect(player2Timer, &QTimer::timeout, this, &SchachApp::updatePlayer2Timer);

    ui->cbPawnPromotion->setCurrentText("Not Selected");
    //connect(ui->pbPawnPromotion, &QPushButton::clicked, this, &SchachApp::onPbPawnPromotionClicked);
    ui->pbPawnPromotion->setEnabled(false);
    ui->cbPawnPromotion->setEnabled(false);

    setWelcomeMessage();
    WelcomeDisplay();
    ui->swpawnpromotion->setCurrentWidget(ui->defaultpage);
    //ui->lblCurrentPlayerName->setText("Welcome to a new game ");

    connect(chessGame, &Game::pieceCaptured, this, &SchachApp::pieceCaptured);

    loadBannedWords();

    ui->currentplayername->setText(LocalName);
    ui->opponentplayername->setText(OpponentName);

}

SchachApp::~SchachApp()
{
    if (client) {
        client->disconnect();
        delete client;
        client = nullptr;
    }

    if (server) {
        server->stopListening();
        delete server;
        server = nullptr;
    }

    delete ui;
    delete chessGame;
}

void SchachApp::WelcomeDisplay(){
    QFont font;
        font.setBold(true);
        font.setPointSize(16); // Increase the font size
        font.setFamily("Arial"); // Set a font family, like Arial or any other you prefer

        ui-> DisplayGame->setFont(font);
        ui-> DisplayGame->setText("Welcome! Please choose your settings");
        ui->DisplayGame->setAlignment(Qt::AlignCenter);

        // Set a gradient background and text color
        ui->DisplayGame->setStyleSheet(
            "color: #ffffff;" // Text color
            "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #3a3a3a, stop:1 #000000);" // Gradient background
            "padding: 10px;" // Padding around the text
            "border-radius: 10px;" // Rounded corners
                    );
}

void SchachApp::StartDisplay(){
    QFont font;
        font.setBold(true);
        font.setPointSize(16); // Increase the font size
        font.setFamily("Arial"); // Set a font family, like Arial or any other you prefer

        ui-> DisplayGame->setFont(font);
        ui-> DisplayGame->setText("Click on Start Game");
        ui->DisplayGame->setAlignment(Qt::AlignCenter);

        // Set a gradient background and text color
        ui->DisplayGame->setStyleSheet(
            "color: #ffffff;" // Text color
            "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #3a3a3a, stop:1 #000000);" // Gradient background
            "padding: 10px;" // Padding around the text
            "border-radius: 10px;" // Rounded corners
                    );
}


void SchachApp::setWelcomeMessage()
{
    QFont font;
        font.setBold(true);
        font.setPointSize(16); // Increase the font size
        font.setFamily("Arial"); // Set a font family, like Arial or any other you prefer

        ui->lblCurrentPlayerName->setFont(font);
        ui->lblCurrentPlayerName->setText("Welcome to a New Game!");

        // Center the text
        ui->lblCurrentPlayerName->setAlignment(Qt::AlignCenter);

        // Set a gradient background and text color
        ui->lblCurrentPlayerName->setStyleSheet(
            "color: #ffffff;" // Text color
            "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #3a3a3a, stop:1 #000000);" // Gradient background
            "padding: 10px;" // Padding around the text
            "border-radius: 10px;" // Rounded corners
        );


}

void SchachApp::initializeBoard()
{
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            buttons[row][col] = nullptr;
            board[row][col] = nullptr;
        }
    }

    if(isLocalPlayerWhite || isLocalGame) {
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


        ui->labelX1->setText("A");
        ui->labelX2->setText("B");
        ui->labelX3->setText("C");
        ui->labelX4->setText("D");
        ui->labelX5->setText("E");
        ui->labelX6->setText("F");
        ui->labelX7->setText("G");
        ui->labelX8->setText("H");


        ui->labelY1->setText("1");
        ui->labelY2->setText("2");
        ui->labelY3->setText("3");
        ui->labelY4->setText("4");
        ui->labelY5->setText("5");
        ui->labelY6->setText("6");
        ui->labelY7->setText("7");
        ui->labelY8->setText("8");

    } else if(!isLocalPlayerWhite){
        buttons[7][7] = ui->A1; buttons[7][6] = ui->B1; buttons[7][5] = ui->C1; buttons[7][4] = ui->D1;
        buttons[7][3] = ui->E1; buttons[7][2] = ui->F1; buttons[7][1] = ui->G1; buttons[7][0] = ui->H1;
        buttons[6][7] = ui->A2; buttons[6][6] = ui->B2; buttons[6][5] = ui->C2; buttons[6][4] = ui->D2;
        buttons[6][3] = ui->E2; buttons[6][2] = ui->F2; buttons[6][1] = ui->G2; buttons[6][0] = ui->H2;
        buttons[5][7] = ui->A3; buttons[5][6] = ui->B3; buttons[5][5] = ui->C3; buttons[5][4] = ui->D3;
        buttons[5][3] = ui->E3; buttons[5][2] = ui->F3; buttons[5][1] = ui->G3; buttons[5][0] = ui->H3;
        buttons[4][7] = ui->A4; buttons[4][6] = ui->B4; buttons[4][5] = ui->C4; buttons[4][4] = ui->D4;
        buttons[4][3] = ui->E4; buttons[4][2] = ui->F4; buttons[4][1] = ui->G4; buttons[4][0] = ui->H4;
        buttons[3][7] = ui->A5; buttons[3][6] = ui->B5; buttons[3][5] = ui->C5; buttons[3][4] = ui->D5;
        buttons[3][3] = ui->E5; buttons[3][2] = ui->F5; buttons[3][1] = ui->G5; buttons[3][0] = ui->H5;
        buttons[2][7] = ui->A6; buttons[2][6] = ui->B6; buttons[2][5] = ui->C6; buttons[2][4] = ui->D6;
        buttons[2][3] = ui->E6; buttons[2][2] = ui->F6; buttons[2][1] = ui->G6; buttons[2][0] = ui->H6;
        buttons[1][7] = ui->A7; buttons[1][6] = ui->B7; buttons[1][5] = ui->C7; buttons[1][4] = ui->D7;
        buttons[1][3] = ui->E7; buttons[1][2] = ui->F7; buttons[1][1] = ui->G7; buttons[1][0] = ui->H7;
        buttons[0][7] = ui->A8; buttons[0][6] = ui->B8; buttons[0][5] = ui->C8; buttons[0][4] = ui->D8;
        buttons[0][3] = ui->E8; buttons[0][2] = ui->F8; buttons[0][1] = ui->G8; buttons[0][0] = ui->H8;

        ui->labelX1->setText("H");
        ui->labelX2->setText("G");
        ui->labelX3->setText("F");
        ui->labelX4->setText("E");
        ui->labelX5->setText("D");
        ui->labelX6->setText("C");
        ui->labelX7->setText("B");
        ui->labelX8->setText("A");


        ui->labelY1->setText("8");
        ui->labelY2->setText("7");
        ui->labelY3->setText("6");
        ui->labelY4->setText("5");
        ui->labelY5->setText("4");
        ui->labelY6->setText("3");
        ui->labelY7->setText("2");
        ui->labelY8->setText("1");
    }

    setupChessBoard();

}

// Setup chessboard in GUI
void SchachApp::setupChessBoard() {
    whiteScore = 0;
    blackScore = 0;
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

    // Update score display (assuming you have labels for scores)
    ui->scorelbl1->setText(QString(" ♔ White Score: %1").arg(whiteScore));
    ui->scorelbl2->setText(QString(" ♚ Black Score: %1").arg(blackScore));
    ui->scorelbl1->setStyleSheet(
        "font-size: 12px;"
        "font-weight: bold;"
        "color: #2c3e50;"
        "font-family: Arial, sans-serif;"
        "padding: 5px;"
    );

    ui->scorelbl2->setStyleSheet(
        "font-size: 12px;"
        "font-weight: bold;"
        "color: #2c3e50;"
        "font-family: Arial, sans-serif;"
        "padding: 5px;"
    );
}




void SchachApp::highlightPossibleMove(const std::pair<int, int>& move) {
    int row = move.second;
    int col = move.first;
    QPushButton* button = buttons[row][col];

    if (button) {
     if (!originalButtonStyles.contains(button)) {
          originalButtonStyles[button] = button->styleSheet(); // Store the current style if not already stored
       }
        button->setStyleSheet("background-color: rgb(255, 231, 142);");
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
    originalButtonStyles.clear(); // Clear the map after resetting
}

void SchachApp::handleSquareClick(int row, int col) {
//    Comment out to play around with the GUI. ERASE COMMENT WHEN SENDING AND RECEIVING MOVES IS IMPLEMENTED
    if ((!isLocalGame && isLocalPlayerWhite != chessGame->getWhiteTurn()) || blockguitmp) {
        updateInGameConsole("Not your turn!");
        return;
    }

    std::shared_ptr<Piece> selectedPiece = chessGame->getPieceAt(col, row);
    // if no piece is selected yet
    if (selectedRow == -1 && selectedCol == -1) {
        // select the piece of the actual player
       if (selectedPiece && ((selectedPiece->checkIfWhite() && chessGame->getWhiteTurn()) || (!selectedPiece->checkIfWhite() && !chessGame->getWhiteTurn()))) {
            chessGame->updateCheckStatus();
            selectedRow = row;
            selectedCol = col;
            qDebug() << "Selected piece at:" << selectedCol << selectedRow;
            // Highlight possible moves for the selected piece
            std::vector<std::pair<int, int>> possibleMoves = selectedPiece->getPossibleMoves(chessGame);
            resetBoardHighlight();  // Clear previous highlights
            for (const auto& move : possibleMoves) {
                if (chessGame->logikInstance.isLegal(chessGame, col, row, move.first, move.second)) {
                    highlightPossibleMove(move);
                }
                // Debug output for possible moves
                for (const auto& move : possibleMoves) {
                    std::cout << move.first << " " << move.second << std::endl;
                }

                previouslySelectedRow = row;
                previouslySelectedCol = col;
            }
        }

    }else{ // if a piece is already selected

              // if another piece of the atual player is selected
            if (selectedPiece && ((selectedPiece->checkIfWhite() && chessGame->getWhiteTurn()) || (!selectedPiece->checkIfWhite() && !chessGame->getWhiteTurn()))) {
                // Clear previous selection highlights if a new piece is selected
                resetBoardHighlight();
                selectedRow = row;
                selectedCol = col;
                qDebug() << "Selected new piece at:" << selectedCol << selectedRow;

                // Highlight possible moves for the newly selected piece
                std::vector<std::pair<int, int>> possibleMoves = selectedPiece->getPossibleMoves(chessGame);

                for (const auto& move : possibleMoves) {
                    if (chessGame->logikInstance.isLegal(chessGame, col, row, move.first, move.second)) {
                        highlightPossibleMove(move);
                    }
                }

                // Debug output for possible moves
                for (const auto& move : possibleMoves) {
                    std::cout << move.first << " " << move.second << std::endl;
                }

                previouslySelectedRow = row;
                previouslySelectedCol = col;
                } else { // Si the case is empty or has an oppenent piece, attempt the movement

        qDebug() << "Attempting to move to:" << col << row;

        // Attempt to move and get MoveInfo
        MoveInfo moveInfo = chessGame->tryMove(selectedCol, selectedRow, col, row);
        qDebug() << "isLegal:" << moveInfo.islegal;

        if (moveInfo.islegal) {  // Move is valid
            movePiece(selectedRow, selectedCol, row, col);
            resetBoardHighlight();
            chessGame->switchTurn();
            startTurnTimer();  // Start the timer for the next turn
            updatecurrentPlayerLabel();

            // Push the moveInfo onto the move history
            chessGame->moveHistory.push_back(moveInfo);

            // Format and display the move into lstMoveHystory
            addMoveToHistory(moveInfo);

            if(!isLocalGame && ((chessGame->getWhiteTurn() && isLocalPlayerWhite) || (!chessGame->getWhiteTurn() && !isLocalPlayerWhite)))
                ui->pbUndo->setEnabled(false);

            if (client) {
                client->sendMove(moveInfo);
            }
            if (server) {
                server->sendMove(moveInfo);
            }

            // Debug output for the board state
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
        } else {
            updateInGameConsole("Illegal move!");
            resetBoardHighlight();  // Clear previous highlights
        }

        // Reset selection
        selectedRow = -1;
        selectedCol = -1;
        }
    }
}

void SchachApp::startTurnTimer() {
 if (isLocalGame){
     if (chessGame->getWhiteTurn()) {
         player1Timer->start(1000);  // Start player 1's timer
         player2Timer->stop();       // Stop player 2's timer
     } else {
         player2Timer->start(1000);  // Start player 2's timer
         player1Timer->stop();       // Stop player 1's timer
     }
 }else {
     if ((isLocalPlayerWhite && chessGame->getWhiteTurn()) ||
         (!isLocalPlayerWhite && !chessGame->getWhiteTurn())) {
         player1Timer->start(1000);  // Start player 1's timer
         player2Timer->stop();       // Stop player 2's timer
     } else {
         player2Timer->start(1000);  // Start player 2's timer
         player1Timer->stop();       // Stop player 1's timer
     }
 }
}

void SchachApp::updateTimerDisplay(int timeRemaining) {
    int minutes = timeRemaining / 60;  // Calculate minutes
    int seconds = timeRemaining % 60;  // Calculate seconds
    QString timeString = QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
    if (isLocalGame) {
        if (chessGame->getWhiteTurn()) {
            ui->lblPlayer1Timer->setText(timeString);  // Update player 1's timer label
        } else {
            ui->lblPlayer2Timer->setText(timeString);  // Update player 2's timer label
        }
    } else {
        if ((isLocalPlayerWhite && chessGame->getWhiteTurn()) ||
            (!isLocalPlayerWhite && !chessGame->getWhiteTurn())) {
            ui->lblPlayer1Timer->setText(timeString);  // Update player 1's timer label
        } else {
            ui->lblPlayer2Timer->setText(timeString);  // Update player 2's timer label
        }
    }
}

void SchachApp::updatePlayer1Timer() {
    if (player1TimeRemaining > 0) {
        player1TimeRemaining--;  // Decrease the remaining time
        updateTimerDisplay(player1TimeRemaining);  // Update the UI for player 1
    } else {
        player1Timer->stop();  // Stop the timer if time runs out
        //handleTimeOut(true);  // Handle timeout for player 1
    }
}

void SchachApp::updatePlayer2Timer() {
    if (player2TimeRemaining > 0) {
        player2TimeRemaining--;  // Decrease the remaining time
        updateTimerDisplay(player2TimeRemaining);  // Update the UI for player 2
    } else {
        player2Timer->stop();  // Stop the timer if time runs out
        //handleTimeOut(false);  // Handle timeout for player 2
    }
}

void SchachApp::updatecurrentPlayerLabel() {
    QFont font;
    font.setBold(true); // Make the font bold
    ui->lblCurrentPlayerName->setFont(font);


    QString labelText;
    QString style;

        if (chessGame->getWhiteTurn()) {
            labelText = "♔ White's Turn";
            style = "color: #000000; font: bold 18px 'Arial';background-color: #ffffff; padding: 10px; border-radius: 5px;";
//            style = "color: #ffffff; font: bold 18px 'Arial';background-color: #000000; padding: 10px; border-radius: 5px;";
        } else {
            labelText = "♚ Black's Turn";
            style = "color: #ffffff; font: bold 18px 'Arial';background-color: #000000; padding: 10px; border-radius: 5px;";
//            style = "color: #000000; font: bold 18px 'Arial';background-color: #ffffff; padding: 10px; border-radius: 5px;";
        }
//    }
    if (isLocalGame) {
        if (player2TimeRemaining <= 0){
            labelText = " ♔ WHITE WINS ♔ ";
            style = "color: #000000; font: bold 18px 'Arial';background-color: #ffffff; padding: 10px; border-radius: 5px;";
//            style = "color: #ffffff; font: bold 18px 'Arial';background-color: #000000; padding: 10px; border-radius: 5px;";
         }else if (player1TimeRemaining <= 0){
            labelText = " ♚ BLACK WINS ♚";
            style = "color: #ffffff; font: bold 18px 'Arial';background-color: #000000; padding: 10px; border-radius: 5px;";
//            style = "color: #000000; font: bold 18px 'Arial';background-color: #ffffff; padding: 10px; border-radius: 5px;";
         }

    } else {
        if ((isLocalPlayerWhite && chessGame->getWhiteTurn()) ||
            (!isLocalPlayerWhite && !chessGame->getWhiteTurn())) {
            if (player1TimeRemaining <= 0){
                        labelText = "You Lose";
                     }
        } else {
            if (player1TimeRemaining <= 0){
                        labelText = "You Win";
                     }
        }
    }

    if (chessGame->isCheckmate == true){
        if (chessGame->getWhiteTurn()){
            labelText = " CHECKMATE ♚ BLACK WINS ♚ ";
        }else{
            labelText = " CHECKMATE ♔ WHITE WINS ♔ ";
        }
        style = R"(
                color: black;
                background-color: #76c7b7;
                padding: 10px 20px;
                border-radius: 15px;
                font-size: 20px;
                font-weight: bold;
                text-align: center;
                border: 2px solid #006400; /* Border color matching text */
            )";
        blockguitmp = true;
        }
    ui->lblCurrentPlayerName->setText(labelText);
    ui->lblCurrentPlayerName->setStyleSheet(style);



}


void SchachApp::movePiece(int fromRow, int fromCol, int toRow, int toCol) {

    if(isLocalGame || (client && client->getopponentgroup() == 1) || (server && server->getopponentgroup() == 1)){ // Enable pbUndo just if local game or network mode but only against group 1
        ui->pbUndo->setEnabled(true); // Enable Undo button after each move (it is disabled if the opponent denies the undo over the network)
    }

    QPushButton* fromButton = buttons[fromRow][fromCol];
    QPushButton* toButton = buttons[toRow][toCol];
    // Move the icon from the selected button to the target button
    toButton->setIcon(fromButton->icon());
    fromButton->setIcon(QIcon());  // Clear the icon from the original button

     // Debugging: Print the move details
     qDebug() << "Moved piece from:" << fromCol << fromRow << "to:" << toCol << toRow;

     // Re-fetch all pieces and update the icons on the board
     for (int row = 0; row < 8; ++row) {
         for (int col = 0; col < 8; ++col) {

             QPushButton* button = buttons[row][col];
             std::shared_ptr<Piece> piece = chessGame->getPieceAt(col, row);  // Get piece from the game

             if (piece != nullptr) {
                 QString iconName = QString(":/Figuren/") + piece->getType() + (piece->checkIfWhite() ? "W" : "B") + ".png";
                 button->setIcon(QIcon(iconName));  // Set the correct icon for the piece

             } else {
                 button->setIcon(QIcon());  // Clear icon if no piece exists
             }
         }
     }
     qDebug() << "score White vs black " << whiteScore <<" vs  " << blackScore;
     // Update score display (assuming you have labels for scores)
         ui->scorelbl1->setText(QString(" ♔ White Score: %1").arg(whiteScore));
         ui->scorelbl2->setText(QString(" ♚ Black Score: %1").arg(blackScore));
         ui->scorelbl1->setStyleSheet(
             "font-size: 12px;"
             "font-weight: bold;"
             "color: #2c3e50;"
             "font-family: Arial, sans-serif;"
             "padding: 5px;"
         );

         ui->scorelbl2->setStyleSheet(
             "font-size: 12px;"
             "font-weight: bold;"
             "color: #2c3e50;"
             "font-family: Arial, sans-serif;"
             "padding: 5px;"
         );

}



quint8 SchachApp::PawnPromotion(int row) {
    quint8 promotionType = 0x00;

    if ((row == 7 && isLocalPlayerWhite) || (row == 0 && !isLocalPlayerWhite) || isLocalGame) {
        qWarning() << "Select a piece for pawn promotion";

        if ((isLocalGame) || (isLocalPlayerWhite && chessGame->getWhiteTurn()) ||
            (!isLocalPlayerWhite && !chessGame->getWhiteTurn())) {
            ui->swpawnpromotion->setCurrentWidget(ui->pawnpromotionpage);
            blockguitmp = true;
        }
        ui->gridLayout->setEnabled(false);
        ui->pbPawnPromotion->setEnabled(true);
        ui->cbPawnPromotion->setEnabled(true);

        // Create a local event loop
        QEventLoop loop;

        // Connect the OK button's clicked signal to a lambda function
        connect(ui->pbPawnPromotion, &QPushButton::clicked, this, [&]() {
            QString mode = ui->cbPawnPromotion->currentText();



            if (mode == "Queen") {
                promotionType = 0x4;
                if (isLocalPlayerWhite) {
                    whiteScore += 8;  // Queen value
                } else {
                    blackScore += 8;  // Queen value
                }
            } else if (mode == "Rook") {
                promotionType = 0x3;
                if (isLocalPlayerWhite) {
                    whiteScore += 4;  // Rook value
                } else {
                    blackScore += 4;  // Rook value
                }
            } else if (mode == "Knight") {
                promotionType = 0x2;
                if (isLocalPlayerWhite) {
                    whiteScore += 2;  // Knight value
                } else {
                    blackScore += 2;  // Knight value
                }
            } else if (mode == "Bishop") {
                promotionType = 0x1;
                if (isLocalPlayerWhite) {
                    whiteScore += 2;  // Bishop value
                } else {
                    blackScore += 2;  // Bishop value
                }
            }
            qDebug() << "Promotion type selected: " << promotionType << mode;

            ui->pbPawnPromotion->setEnabled(false);
            ui->cbPawnPromotion->setEnabled(false);
            ui->swpawnpromotion->setCurrentWidget(ui->defaultpage);
            blockguitmp = false;

            // Exit the event loop when the button is clicked
            loop.quit();
        });

        // Start the event loop, this will block until loop.quit() is called
        loop.exec();
    }
    ui->gridLayout->setEnabled(true);
    // Update score display (assuming you have labels for scores)
    ui->scorelbl1->setText(QString(" ♔ White Score: %1").arg(whiteScore));
    ui->scorelbl2->setText(QString(" ♚ Black Score: %1").arg(blackScore));
    ui->scorelbl1->setStyleSheet(
        "font-size: 12px;"
        "font-weight: bold;"
        "color: #2c3e50;"
        "font-family: Arial, sans-serif;"
        "padding: 5px;"
    );

    ui->scorelbl2->setStyleSheet(
        "font-size: 12px;"
        "font-weight: bold;"
        "color: #2c3e50;"
        "font-family: Arial, sans-serif;"
        "padding: 5px;"
    );
    return promotionType;
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
    ui->leIP->setEnabled(false);
    ui->spnPort->setEnabled(false);
    if(ui->cbHostClient->currentText() == "Client") {
        if(client->isConnected()) {
            client->disconnect();
        } else {
            auto ip = ui->leIP->text();
            auto port = ui->spnPort->value();
            client->connectToHost(ip, port);
            // Print connection error after some time if disconnected (SocketError gibt Probleme im online builder)
            // Disable bConnect while trying to connect
            ui->bConnect->setEnabled(false);
            ui->cbHostClient->setEnabled(false);
            QTimer::singleShot(500, this, [this]() {
                if(client->state() == QAbstractSocket::ConnectedState) {
                    ui->bConnect->setEnabled(true);
                    ui->cbHostClient->setEnabled(true);
                } else {
                    QTimer::singleShot(3000, this, [this]() {
                        if(client->state() != QAbstractSocket::ConnectedState) {
                            ui->lstNetzwerkConsole->addItem("Connection error. Check IP Address or Host availability");
                            ui->lstNetzwerkConsole->scrollToBottom();
                        }
                        ui->bConnect->setEnabled(true);
                        ui->cbHostClient->setEnabled(true);
                        });
            }
            });
        }
    } else if(ui->cbHostClient->currentText() == "Server") {
        if(server->isListening()) {
            // Stop listening if the server is already listening
            server->stopListening();
            ui->bConnect->setText("Start Listening");
            ui->lstNetzwerkConsole->addItem("Server stopped listening.");
            ui->lstNetzwerkConsole->scrollToBottom();
        } else {
            // Get the port number from the spnPort widget and start listening
            int port = ui->spnPort->value();
            server->startListening(port);
            ui->bConnect->setText("Stop Listening");
        }
    }
}

void SchachApp::on_cbHostClient_currentTextChanged(const QString &mode) {
    if(mode == "Client") {
        isLocalGame = false;
        // Update bConnect button for client
        ui->bConnect->setText("Connect");

        ui->bStart->setEnabled(false);
        ui->leIP->setEnabled(true);
        ui->spnPort->setEnabled(true);
        ui->cbStartingPlayer->setEnabled(false);
        ui->bConnect->setEnabled(true);

        // Switch to Client mode
        if(server) {
            server->disconnect();
            server->stopListening();
            delete server;
            server = nullptr;
            ui->lstNetzwerkConsole->addItem("Switched to Client Mode. Server stopped.");
            ui->lstNetzwerkConsole->scrollToBottom();
        }

        if(!client) {
            client = new MyTCPClient(chessGame);
            setDeviceController();
            ui->lstNetzwerkConsole->addItem("Client initialized.");
            ui->lstNetzwerkConsole->scrollToBottom();
            connect(client, &Netzwerk::logNetzwerkMsg, this, &SchachApp::updateNetzwerkConsole);
            connect(client, &Netzwerk::logInGameMsg, this, &SchachApp::updateInGameConsole);
            connect(client, &Netzwerk::gameStarted, this, &SchachApp::gameStarted);
            connect(client, &Netzwerk::moveReceived, this, &SchachApp::moveReceived);
            connect(client, &Netzwerk::undoMove, this, &SchachApp::undoMove);
            connect(client, &Netzwerk::ChatMsgReceived, this, &SchachApp::onChatMsgReceived);
            connect(client, &Netzwerk::moveRejected, this, &SchachApp::undoMove);
            connect(client, &Netzwerk::opponentNameReceived, this, &SchachApp::opponentNameReceived);
        }
    } else if(mode == "Server") {
        isLocalGame = false;
        //Update bConnect button for server
        ui->bConnect->setText("Start Listening");

        ui->bStart->setEnabled(false);
        ui->leIP->setEnabled(false);
        ui->spnPort->setEnabled(true);
        ui->cbStartingPlayer->setEnabled(true);
        ui->bConnect->setEnabled(true);

        // Switch to Server mode
        if(client) {
            client->disconnect();
            delete client;
            client = nullptr;
            ui->lstNetzwerkConsole->addItem("Switched to Server Mode. Client stopped.");
            ui->lstNetzwerkConsole->scrollToBottom();
        }

        if(!server) {
            server = new MyTCPServer(chessGame);
            ui->lstNetzwerkConsole->addItem("Server initialized");
            ui->lstNetzwerkConsole->scrollToBottom();
            connect(server, &MyTCPServer::clientStateChanged, this, &SchachApp::updateNetzwerkConsole);
            connect(server, &MyTCPServer::clientStateChanged, this, [=]() {
                    ui->bStart->setEnabled(true);
                    StartDisplay();
                });
            connect(server, &Netzwerk::logNetzwerkMsg, this, &SchachApp::updateNetzwerkConsole);
            connect(server, &Netzwerk::logInGameMsg, this, &SchachApp::updateInGameConsole);
            connect(server, &MyTCPServer::serverStatus, this, &SchachApp::updateNetzwerkConsole);
            connect(server, &Netzwerk::moveReceived, this, &SchachApp::moveReceived);
            connect(server, &Netzwerk::undoMove, this, &SchachApp::undoMove);
            connect(server, &Netzwerk::ChatMsgReceived, this, &SchachApp::onChatMsgReceived);
            connect(server, &MyTCPServer::client_Connected, this, &SchachApp::on_client_connected);
            connect(server, &MyTCPServer::client_Disconnected, this, &SchachApp::on_client_disconnected);
            connect(server, &Netzwerk::moveRejected, this, &SchachApp::undoMove);
            connect(server, &Netzwerk::opponentNameReceived, this, &SchachApp::opponentNameReceived);
        }
    } else if(mode == "Local") {
        isLocalGame = true;
        ui->bConnect->setEnabled(false);
        ui->bConnect->setText("Connect");

        ui->bStart->setEnabled(true);
        ui->leIP->setEnabled(false);
        ui->spnPort->setEnabled(false);
        ui->cbStartingPlayer->setEnabled(false);
        StartDisplay();

        ui->lstChat->setEnabled(false);
        ui->leSendChat->setEnabled(false);

        ui->bSendName->setEnabled(false);
        ui->lename->setEnabled(false);

        if(server) {
            server->stopListening();
            delete server;
            server = nullptr;
            ui->lstNetzwerkConsole->addItem("Switched to Client Mode. Server stopped.");
            ui->lstNetzwerkConsole->scrollToBottom();
        }

        if(client) {
            client->disconnect();
            delete client;
            client = nullptr;
            ui->lstNetzwerkConsole->addItem("Switched to Server Mode. Client stopped.");
            ui->lstNetzwerkConsole->scrollToBottom();
        }
    }
}

void SchachApp::updateNetzwerkConsole(QString message) {
    ui->lstNetzwerkConsole->addItem(message);
    ui->lstNetzwerkConsole->scrollToBottom();
}

void SchachApp::updateInGameConsole(QString message) {
    ui->lstInGameConsole->addItem(message);
    ui->lstInGameConsole->scrollToBottom();
}

void SchachApp::setDeviceController() {
    if(client) {
    connect(client, &MyTCPClient::connected, this, &SchachApp::device_connected);
    connect(client, &MyTCPClient::disconnected, this, &SchachApp::device_disconnected);
    connect(client, &MyTCPClient::stateChanged, this, &SchachApp::device_stateChanged);
    }
}

void SchachApp::device_connected() {
    ui->lstNetzwerkConsole->addItem("Connected to device");
    ui->lstNetzwerkConsole->scrollToBottom();
    ui->bConnect->setText("Disconnect");
    ui->lstChat->setEnabled(true);
    ui->leSendChat->setEnabled(true);
    ui->bSendName->setEnabled(true);
    ui->lename->setEnabled(true);
}

void SchachApp::device_disconnected() {
    ui->lstNetzwerkConsole->addItem("Disconnected from host");
    ui->lstNetzwerkConsole->scrollToBottom();
    client->tryReconnect();
    ui->bConnect->setText("Connect");
    ui->lstChat->setEnabled(false);
    ui->leSendChat->setEnabled(false);
    ui->bSendName->setEnabled(false);
    ui->lename->setEnabled(false);
}

void SchachApp::device_stateChanged(QAbstractSocket::SocketState state) {
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    ui->lstNetzwerkConsole->addItem(metaEnum.valueToKey(state));
    ui->lstNetzwerkConsole->scrollToBottom();
}

void SchachApp::moveReceived(MoveInfo moveInfo) {

    MoveInfo result = chessGame->tryMove(moveInfo.s_col, moveInfo.s_row, moveInfo.e_col, moveInfo.e_row, moveInfo.promotion);

    if(result.islegal) {
        movePiece(moveInfo.s_row, moveInfo.s_col, moveInfo.e_row, moveInfo.e_col);
        updateNetzwerkConsole("Opponent's move applied.");
        chessGame->switchTurn();
        startTurnTimer();  // Start the timer for the next turn
        updatecurrentPlayerLabel();

        // Push the moveInfo onto the move history
        chessGame->moveHistory.push_back(moveInfo);

        chessGame->updateCheckStatus();

        // Format and display the move
        addMoveToHistory(moveInfo);

        if(!isLocalGame && ((chessGame->getWhiteTurn() && isLocalPlayerWhite) || (!chessGame->getWhiteTurn() && !isLocalPlayerWhite)))
            ui->pbUndo->setEnabled(false);

    } else {
        updateNetzwerkConsole("Invalid move received");
    }
}




// Client version of gameStarted()
void SchachApp::gameStarted(bool ServerStarts, QString groupNumber) {
        qDebug() << "gameStarted" << ServerStarts;
        isLocalGame = false;
        ui->cbHostClient->setEnabled(false);
        ui->lstInGameConsole->clear();
        startTurnTimer();
        updatecurrentPlayerLabel();
        if(ServerStarts) {
            updateInGameConsole("Server starts the game.");
            updateInGameConsole("Playing against Group " + groupNumber);
            isLocalPlayerWhite = false;
        } else {
            updateInGameConsole("Client starts the game.");
            updateInGameConsole("Playing against Group " + groupNumber);
            isLocalPlayerWhite = true;
        }
        initializeBoard();
        ui->GAME ->setCurrentWidget(ui->gamepage);
}

void SchachApp::on_cbStartingPlayer_currentTextChanged(const QString &startingPlayer) {
    qDebug() << "startingGame" << startingPlayer;
    if(startingPlayer == "Server") {
        isLocalPlayerWhite = true;
    } else if(startingPlayer == "Client") {
        isLocalPlayerWhite = false;
    }

}

void SchachApp::on_bStart_clicked()
{
    if(!isLocalGame) {
        bool ServerStarts = (ui->cbStartingPlayer->currentText() == "Server");
        server->sendGameStart(ServerStarts);
        updateNetzwerkConsole("Game start message sent. " + ui->cbStartingPlayer->currentText() + " starts.");
    }

    ui->lstInGameConsole->clear();
    ui->bStart->setEnabled(false);
    ui->cbHostClient->setEnabled(false);
    ui->leIP->setEnabled(false);
    ui->cbStartingPlayer->setEnabled(false);
    ui->spnPort->setEnabled(false);
    startTurnTimer();
    updatecurrentPlayerLabel();
    initializeBoard();
    ui->GAME ->setCurrentWidget(ui->gamepage);
}

void SchachApp::undoMove() {

    if (chessGame->moveHistory.empty()) {
        updateNetzwerkConsole("No moves to undo");
        return;
    }

    bool stopundo = false;

    if (!isLocalGame && ((client && client->undoMovetmp == true) || (server && server->undoMovetmp == true))) {

        ui->pbUndoAccept->setEnabled(true);

        ui->pbUndoDeny->setEnabled(true);

        ui->pbUndo->setEnabled(false);

        QEventLoop loop;

        auto conn1 = std::make_shared<QMetaObject::Connection>();
        auto conn2 = std::make_shared<QMetaObject::Connection>();

        *conn1 = connect(ui->pbUndoDeny, &QPushButton::clicked, this, [&]() {
            if(client) client->sendUndoResponse(false);
            if(server) server->sendUndoResponse(false);
            if(isLocalGame || (client && client->getopponentgroup() == 1) || (server && server->getopponentgroup() == 1)){ // Enable pbUndo just if local game or network mode but only against group 1
                ui->pbUndo->setEnabled(true); // Enable Undo button after each move (it is disabled if the opponent denies the undo over the network)
            }

            ui->pbUndoAccept->setEnabled(false);

            ui->pbUndoDeny->setEnabled(false);

            // Exit the event loop when the button is clicked
            stopundo = true;
            disconnect(*conn1);
            loop.quit();
        });

        *conn2 = connect(ui->pbUndoAccept, &QPushButton::clicked, this, [&]() {
            if(client) client->sendUndoResponse(true);
            if(server) server->sendUndoResponse(true);

            // Exit the event loop when the button is clicked

            ui->pbUndoAccept->setEnabled(false);


            ui->pbUndoDeny->setEnabled(false);
            if(isLocalGame || (client && client->getopponentgroup() == 1) || (server && server->getopponentgroup() == 1)){ // Enable pbUndo just if local game or network mode but only against group 1
                ui->pbUndo->setEnabled(true); // Enable Undo button after each move (it is disabled if the opponent denies the undo over the network)
            }
            disconnect(*conn2);
            loop.quit();
        });

        loop.exec();
    }

    if(client) client->undoMovetmp = false;
    else if(server) server->undoMovetmp = false;

    if(stopundo) return;

    MoveInfo lastMove = chessGame->moveHistory.back();
    chessGame->moveHistory.pop_back();

    // Undo the move in the game logic
    chessGame->undoMove(lastMove);

    // Update the GUI
    // Re-fetch all pieces and update the icons on the board
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            QPushButton* button = buttons[row][col];
            std::shared_ptr<Piece> piece = chessGame->getPieceAt(col, row);  // Get piece from the game

            if (piece != nullptr) {
                QString iconName = QString(":/Figuren/") + piece->getType() + (piece->checkIfWhite() ? "W" : "B") + ".png";
                button->setIcon(QIcon(iconName));  // Set the correct icon for the piece
            } else {
                button->setIcon(QIcon());  // Clear icon if no piece exists
            }
        }
    }

    // Update other game states, timers, labels
    startTurnTimer();    // Restart the timer for the player whose turn it now is
    updatecurrentPlayerLabel();

    // Remove the move from the move history display and disable the button if it´s empty
    removeLastMoveFromHistory();
    ui->pbUndo->setEnabled(!chessGame->moveHistory.empty());
    if(chessGame->moveHistory.empty()) {
        player1TimeRemaining = 10*60;
        player2TimeRemaining = 10*60;
        ui->lblPlayer1Timer->setText("10:00");
        ui->lblPlayer2Timer->setText("10:00");

    }
}
void SchachApp::on_pbClear_clicked()
{
    ui->lstNetzwerkConsole->clear();
}

QString SchachApp::formatMove(const MoveInfo& moveInfo) {
    // Get the moving piece
    std::shared_ptr<Piece> movingPiece = chessGame->getPieceAt(moveInfo.e_col, moveInfo.e_row);
    if (!movingPiece) {
        return "";
    }

    QString moveNotation;

    // Handle castling
    if (movingPiece->getType() == "king" && abs(moveInfo.e_col - moveInfo.s_col) == 2) {
        if (moveInfo.e_col == 6) { // Kingside castling
            moveNotation = "O-O";
        } else if (moveInfo.e_col == 2) { // Queenside castling
            moveNotation = "O-O-O";
        }
    } else {
        // For other pieces
        QString pieceNotation;
        if (movingPiece->getType() == "pawn") {
            pieceNotation = "";
        } else if (movingPiece->getType() == "knight") {
            pieceNotation = "N";
        } else if (movingPiece->getType() == "bishop") {
            pieceNotation = "B";
        } else if (movingPiece->getType() == "rook") {
            pieceNotation = "R";
        } else if (movingPiece->getType() == "queen") {
            pieceNotation = "Q";
        } else if (movingPiece->getType() == "king") {
            pieceNotation = "K";
        }

        // Determine if it's a capture
        bool isCapture = moveInfo.capturedPiece != nullptr || moveInfo.enPassantCapturedPawn != nullptr;
        if (movingPiece->getType() == "pawn" && isCapture) {
            // For pawn captures, include the file (column) of the pawn
            pieceNotation += QChar('a' + moveInfo.s_col);
        }

        QString captureNotation = isCapture ? "x" : "";

        // Destination square
        QString destFile = QChar('a' + moveInfo.e_col);
        QString destRank = QString::number(moveInfo.e_row + 1);

        // Promotion
        QString promotionNotation;
        if (moveInfo.promotion != 0x00) {
            // Assuming promotion codes match the piece types
            if (moveInfo.promotion == 0x40) { // Queen
                promotionNotation = "=Q";
            } else if (moveInfo.promotion == 0x30) { // Rook
                promotionNotation = "=R";
            } else if (moveInfo.promotion == 0x20) { // Knight
                promotionNotation = "=N";
            } else if (moveInfo.promotion == 0x10) { // Bishop
                promotionNotation = "=B";
            }
        }

        // Check or checkmate notation
        QString checkNotation;
        if (moveInfo.consequences & 0x02) { // Checkmate
            checkNotation = "#";
        } else if (chessGame->getCheck(!movingPiece->checkIfWhite())) { // If opponent is in check
            checkNotation = "+";
        }

        moveNotation = pieceNotation + captureNotation + destFile + destRank + promotionNotation + checkNotation;
    }

    return moveNotation;
}

void SchachApp::addMoveToHistory(const MoveInfo& moveInfo) {
    QString moveNotation = formatMove(moveInfo);

    // Determine if it's white's or black's move based on move count
    int moveNumber = (chessGame->moveHistory.size() + 1) / 2;

    if (chessGame->moveHistory.size() % 2 == 1) {
        // White's move
        QString entry = QString::number(moveNumber) + ". " + moveNotation;
        ui->lstMoveHistory->addItem(entry);
    } else {
        // Black's move
        QListWidgetItem* lastItem = ui->lstMoveHistory->item(ui->lstMoveHistory->count() - 1);
        lastItem->setText(lastItem->text() + " " + moveNotation);
    }

    // Scroll to the bottom to show the latest move
    ui->lstMoveHistory->scrollToBottom();
}

void SchachApp::removeLastMoveFromHistory() {
    if (ui->lstMoveHistory->count() == 0) {
        return;
    }

    if (chessGame->moveHistory.size() % 2 != 0) {
        // Last move was a black move
        QListWidgetItem* lastItem = ui->lstMoveHistory->item(ui->lstMoveHistory->count() - 1);
        QString text = lastItem->text();
        int spaceIndex = text.lastIndexOf(' ');

        if (spaceIndex != -1) {
            text = text.left(spaceIndex);
            lastItem->setText(text);
        } else {
            delete ui->lstMoveHistory->takeItem(ui->lstMoveHistory->count() - 1);
        }
    } else {
        // Last move was a white move
        delete ui->lstMoveHistory->takeItem(ui->lstMoveHistory->count() - 1);
    }
}



void SchachApp::pieceCaptured(std::shared_ptr<Piece> capturedPiece) {
    QString type = capturedPiece->getType();
    QLabel *capturedPieceLabel = new QLabel();
    QString imagePath = QString(":/Figuren/") + type + (capturedPiece->checkIfWhite() ? "W" : "B") + ".png";

    QPixmap originalPixmap(imagePath);
    QSize newSize(32, 32);
    QPixmap scaledPixmap = originalPixmap.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    capturedPieceLabel->setPixmap(QPixmap(scaledPixmap));

    // Calculate piece value
    int pieceValue = 0;
    if (type == "pawn") pieceValue = 1;
    else if (type == "horse" || type == "bishop") pieceValue = 3;
    else if (type == "rook") pieceValue = 5;
    else if (type == "queen") pieceValue = 9;



    CapturedPieceInfo info = {type, capturedPiece->checkIfWhite(), pieceValue};
    capturedPiecesStack.push(info);

    if (capturedPiece->checkIfWhite()) {
        ui->deadplayer1->addWidget(capturedPieceLabel);
        blackScore += pieceValue;
    } else {
        ui->deadplayer2->addWidget(capturedPieceLabel);
        whiteScore += pieceValue;
    }
    // Update score display (assuming you have labels for scores)
    ui->scorelbl1->setText(QString(" ♔ White Score: %1").arg(whiteScore));
    ui->scorelbl2->setText(QString(" ♚ Black Score: %1").arg(blackScore));

    ui->scorelbl1->setStyleSheet(
        "font-size: 12px;"
        "font-weight: bold;"
        "color: #2c3e50;"
        "font-family: Arial, sans-serif;"
        "padding: 5px;"
    );

    ui->scorelbl2->setStyleSheet(
        "font-size: 12px;"
        "font-weight: bold;"
        "color: #2c3e50;"
        "font-family: Arial, sans-serif;"
        "padding: 5px;"
    );

}

void SchachApp::undoScoreUpdate() {
    if (!capturedPiecesStack.isEmpty()) {
        // Retrieve the last captured piece information
        CapturedPieceInfo lastCapturedPiece = capturedPiecesStack.pop();

        // Undo the score update
        if (lastCapturedPiece.isWhite) {
            blackScore -= lastCapturedPiece.value;

            // Remove the last piece from the dead pieces display for black
            if (ui->deadplayer1->count() > 0) {
                // Access the last widget by iterating through the layout items
                QLayoutItem* lastItem = ui->deadplayer1->itemAt(ui->deadplayer1->count() - 1);
                if (lastItem) {
                    QWidget* lastPiece = lastItem->widget();
                    ui->deadplayer1->removeWidget(lastPiece);
                    delete lastPiece; // Delete widget to free memory
                }
            }
        } else {
            whiteScore -= lastCapturedPiece.value;

            // Remove the last piece from the dead pieces display for white
            if (ui->deadplayer2->count() > 0) {
                // Access the last widget by iterating through the layout items
                QLayoutItem* lastItem = ui->deadplayer2->itemAt(ui->deadplayer2->count() - 1);
                if (lastItem) {
                    QWidget* lastPiece = lastItem->widget();
                    ui->deadplayer2->removeWidget(lastPiece);
                    delete lastPiece; // Delete widget to free memory
                }
            }
        }

        // Update the score labels
        // Update score display (assuming you have labels for scores)
        ui->scorelbl1->setText(QString(" ♔ White Score: %1").arg(whiteScore));
        ui->scorelbl2->setText(QString(" ♚ Black Score: %1").arg(blackScore));

        ui->scorelbl1->setStyleSheet(
            "font-size: 12px;"
            "font-weight: bold;"
            "color: #2c3e50;"
            "font-family: Arial, sans-serif;"
            "padding: 5px;"
        );

        ui->scorelbl2->setStyleSheet(
            "font-size: 12px;"
            "font-weight: bold;"
            "color: #2c3e50;"
            "font-family: Arial, sans-serif;"
            "padding: 5px;"
        );
    }
}


void SchachApp::on_pbUndo_clicked() {

    bool acceptedmain = true;

    if(!isLocalGame) {
        if(client) client->sendUndo();
        else if(server) server->sendUndo();
        ui->pbUndo->setEnabled(false);
        blockguitmp = true;
        acceptedmain = false;

        QEventLoop loop;

        if(client)
            connect(client, &Netzwerk::undoAccepted, this, [&](bool accepted) {
                if(accepted){
                    if(isLocalGame || (client && client->getopponentgroup() == 1) || (server && server->getopponentgroup() == 1)){ // Enable pbUndo just if local game or network mode but only against group 1
                        ui->pbUndo->setEnabled(true); // Enable Undo button after each move (it is disabled if the opponent denies the undo over the network)
                    }
                }
                else ui->pbUndo->setEnabled(false);
                blockguitmp = false;
                acceptedmain = accepted;
                loop.quit();
            });
        if(server)
            connect(server, &Netzwerk::undoAccepted, this, [&](bool accepted) {
                if(accepted){
                    if(isLocalGame || (client && client->getopponentgroup() == 1) || (server && server->getopponentgroup() == 1)){ // Enable pbUndo just if local game or network mode but only against group 1
                        ui->pbUndo->setEnabled(true); // Enable Undo button after each move (it is disabled if the opponent denies the undo over the network)
                    }
                }
                else ui->pbUndo->setEnabled(false);
                blockguitmp = false;
                acceptedmain = accepted;
                loop.quit();
            });

        loop.exec();
    }

    if(acceptedmain) {
        qDebug() << "Undoing the move";
        undoMove();
        undoScoreUpdate();

    }

}

void SchachApp::on_leSendChat_returnPressed()
{
    QString originalMessage = ui->leSendChat->text();
    QString censoredMessage = censorMessage(originalMessage);

    ui->leSendChat->clear();

    // Check if any words were censored
    if(originalMessage != censoredMessage) {
        ui->lstChat->addItem("You: " + censoredMessage + " [Censored]");
    }
    else {
        ui->lstChat->addItem("You: " + censoredMessage);
    }

    ui->lstChat->scrollToBottom();

    // Send the censored message
    if(client) {
        client->sendChatMsg(originalMessage);
    }
    else if(server) {
        server->sendChatMsg(originalMessage);
    }

}

void SchachApp::onChatMsgReceived(QString message) {
    QString originalMessage = message;
    QString censoredMessage = censorMessage(originalMessage);

    // Check if any words were censored
    if(originalMessage != censoredMessage) {
        ui->lstChat->addItem("Opponent: " + censoredMessage + " [Censored]");
    }
    else {
        ui->lstChat->addItem("Opponent: " + censoredMessage);
    }
    ui->lstChat->scrollToBottom();
}

void SchachApp::on_client_connected() {
    ui->bSendName->setEnabled(true);
    ui->lename->setEnabled(true);
    ui->lstChat->setEnabled(true);
    ui->leSendChat->setEnabled(true);
}

void SchachApp::on_client_disconnected() {
    ui->bSendName->setEnabled(false);
    ui->lename->setEnabled(false);
    ui->lstChat->setEnabled(false);
    ui->leSendChat->setEnabled(false);
}

void SchachApp::loadBannedWords() {
    QFile fileEn(bannedWordsFilePathEn);

    if (!fileEn.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open banned words file:" << bannedWordsFilePathEn;
        return;
    }

    QTextStream En(&fileEn);
    while (!En.atEnd()) {
        QString line = En.readLine().trimmed();
        if (!line.isEmpty()) {
            bannedWords.append(line.toLower());
        }
    }

    fileEn.close();

    QFile fileDe(bannedWordsFilePathDe);

    if (!fileDe.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open banned words file:" << bannedWordsFilePathDe;
        return;
    }

    QTextStream De(&fileDe);
    while (!De.atEnd()) {
        QString line = De.readLine().trimmed();
        if (!line.isEmpty()) {
            bannedWords.append(line.toLower());
        }
    }

    fileDe.close();

    qDebug() << "Loaded" << bannedWords.size() << "banned words.";
}

QString SchachApp::censorMessage(const QString& message) const {
    QString censoredMessage = message;
    QString lowerMessage = message.toLower();

    for (const QString& word : bannedWords) {
        // Create a case-insensitive regular expression with word boundaries
        QRegularExpression regex(QString("\\b%1\\b").arg(QRegularExpression::escape(word)),
                                 QRegularExpression::CaseInsensitiveOption);

        // Create a replacement string with asterisks matching the word's length
        QString replacement = QString("*").repeated(word.length());

        // Replace all occurrences of the banned word
        censoredMessage.replace(regex, replacement);
    }

    return censoredMessage;
}

void SchachApp::on_bSendName_clicked()
{
    LocalName = ui->lename->text();
    ui->currentplayername->setText(LocalName);
    if(client) client->sendName(LocalName);
    if(server) server->sendName(LocalName);
}

void SchachApp::on_lename_returnPressed()
{
    on_bSendName_clicked();
}

void SchachApp::opponentNameReceived(QString oppName) {
    OpponentName = oppName;
    ui->opponentplayername->setText(OpponentName);
}
